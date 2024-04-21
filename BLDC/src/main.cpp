#include "Arduino.h"
#include "SPI.h"
#include "SimpleFOC.h"
#include "SimpleFOCDrivers.h"
#include "encoders/as5047/MagneticSensorAS5047.h"


#define SPI_2_MISO  4
#define SPI_2_MOSI  3
#define SPI_2_SCK   2
#define SENSOR1_CS  5 

// magnetic sensor instance - SPI

MagneticSensorAS5047 sensor(SENSOR1_CS, true);
MbedSPI spi2(SPI_2_MISO, SPI_2_MOSI, SPI_2_SCK);

// BLDC motor & driver instance
BLDCDriver3PWM driver = BLDCDriver3PWM(21, 20, 19, 22);
BLDCMotor motor = BLDCMotor(11, 9.75);

// commander interface
Commander command = Commander(Serial);
void onTarget(char* cmd){ command.target(&motor,cmd); }
void onMotor(char* cmd){ command.motor(&motor, cmd); }
void onMotion(char* cmd){ command.motion(&motor,cmd); }

void setup() {
  spi2.begin();
  sensor.init(&spi2);
  // initialise magnetic sensor hardware
  sensor.init();
  // link the motor to the sensor
  motor.linkSensor(&sensor);

  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 12;
  driver.init();
  // link driver
  motor.linkDriver(&driver);

  // set control loop type to be used
  motor.controller = MotionControlType::angle;

  // contoller configuration based on the control type 
  motor.PID_velocity.P = .125;
  motor.PID_velocity.I = 7;
  // motor.PID_velocity.D = 0.001;
  // default voltage_power_supply
  motor.voltage_limit = 10;
  motor.PID_velocity.output_ramp = 1000;


  // velocity low pass filtering time constant
  motor.LPF_velocity.Tf = 0.045;

  // angle loop controller
  motor.P_angle.P = 8.0;
  motor.velocity_limit = 50;
  motor.current_limit = .3;
  
  Serial.begin(115200);
  motor.useMonitoring(Serial);

  // initialise motor
  motor.init();
  // align encoder and start FOC
  motor.initFOC();

  // set the inital target value
  motor.target = M_PI/4;

  // define the motor id
  command.add('A', onMotor, "motor");
  command.add('M',onMotion,"motion control");
  
  // Run user commands to configure and the motor (find the full command list in docs.simplefoc.com)
  Serial.println(F("Motor commands sketch | Initial motion control > torque/voltage : target 2V."));
  motor.monitor_variables = _MON_TARGET | _MON_VEL | _MON_ANGLE ; 
  motor.monitor_downsample = 100; 
  _delay(1000);
}


//float target_angle = sin(0);
//long timestamp_us = _micros();
//float target_velocity = 2; // 2Rad/s ~ 20rpm
//float d_T = .00;

void loop() {

  motor.loopFOC();
  
  //motor.move(2*sin(d_T));
  motor.move();


  // user communication
  command.run();
  motor.monitor();
  //d_T += .0001;
}