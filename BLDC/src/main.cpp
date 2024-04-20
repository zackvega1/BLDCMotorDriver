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
void onMotor(char* cmd){ command.motor(&motor, cmd); }

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
  motor.controller = MotionControlType::torque;

  // contoller configuration based on the control type 
  motor.PID_velocity.P = 0.2;
  motor.PID_velocity.I = 20;
  motor.PID_velocity.D = 0;
  // default voltage_power_supply
  motor.voltage_limit = 12;

  // velocity low pass filtering time constant
  motor.LPF_velocity.Tf = 0.01;

  // angle loop controller
  motor.P_angle.P = 20;
  // angle loop velocity limit
  motor.velocity_limit = 50;

  // use monitoring with serial for motor init
  // monitoring port
  Serial.begin(115200);
  // comment out if not needed
  motor.useMonitoring(Serial);

  // initialise motor
  motor.init();
  // align encoder and start FOC
  motor.initFOC();

  // set the inital target value
  motor.target = 2;

  // define the motor id
  command.add('A', onMotor, "motor");

  // Run user commands to configure and the motor (find the full command list in docs.simplefoc.com)
  Serial.println(F("Motor commands sketch | Initial motion control > torque/voltage : target 2V."));
  
  _delay(1000);
}


void loop() {
  // iterative setting of the FOC phase voltage
  motor.loopFOC();

  // iterative function setting the outter loop target
  // velocity, position or voltage
  // if target not set in parameter uses motor.target variable
  motor.move();
  
  // user communication
  command.run();
}