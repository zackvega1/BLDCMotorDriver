#include "Arduino.h"
#include "SPI.h"
#include "SimpleFOC.h"
#include "SimpleFOCDrivers.h"
#include "encoders/as5047/MagneticSensorAS5047.h"

#define SPI_2_MISO  4
#define SPI_2_MOSI  3
#define SPI_2_SCK   2
#define SENSOR1_CS  1 // some digital pin that you're using as the nCS pin

MagneticSensorAS5047 sensor1(SENSOR1_CS, true);
MbedSPI spi2(SPI_2_MISO, SPI_2_MOSI, SPI_2_SCK);

//driver setup
//  BLDCDriver3PWM( pin_pwmA, pin_pwmB, pin_pwmC, enable (optional))
//TODO: check pins
BLDCDriver3PWM driver = BLDCDriver3PWM(20, 20, 19, 30);

//current sensing setup
//  InlineCurrentSense(shunt_resistance, gain, adc_a, adc_b)
//TODO: check values
//10Megaohm resistor to 0.001 = 1 milliohm from documentation
InlineCurrentSense current_sense = InlineCurrentSense(10000000, 50, 31, 31);

//motor setup
//  BLDCMotor( pole_pairs , ( phase_resistance, KV_rating  optional) )
//TODO: Check pole pairs
BLDCMotor motor = BLDCMotor(11);


void setup() {
  // init sensor
  spi2.begin();
  sensor1.init(&spi2);

  // pwm frequency to be used [Hz]
  driver.pwm_frequency = 20000;
  // power supply voltage [V]
  driver.voltage_power_supply = 12; //check this
  // Max DC voltage allowed - default voltage_power_supply
  driver.voltage_limit = 12;
  // driver init
  driver.init();
  
  // link the driver with the current sense
  current_sense.linkDriver(&driver);
  // init current sense
  current_sense.init();

  // link the motor to the sensor
  motor.linkSensor(&sensor1);

  // init driver
  // link the motor to the driver
  motor.linkDriver(&driver);
  // link driver and the current sense
  
  // link the motor to current sense
  motor.linkCurrentSense(&current_sense);

  // set control loop type to be used
  motor.controller = MotionControlType::velocity;
  // initialize motor
  motor.init();
}

void loop() {
 // update the sensor (only needed if using the sensor without a motor)
  sensor1.update();

  // get the angle, in radians, including full rotations
  float a1 = sensor1.getAngle();
  float degs = a1*180/M_PI;
  //Serial.println(a1);
  // get the velocity, in rad/s - note: you have to call getAngle() on a
  // regular basis for it to work
  float v1 = sensor1.getVelocity();
  // get the angle, in radians, no full rotations
  float a2 = sensor1.getCurrentAngle();
  // Serial.println(a2);
  //  get the raw 14 bit value
  uint16_t raw = sensor1.readRawAngle();
  // read the CORDIC magnitude value, a measure of the magnet field strength
  float m1 = sensor1.readMagnitude();
  // check for errors
  if (sensor1.isErrorFlag()) {
    AS5047Error error = sensor1.clearErrorFlag();
    if (error.parityError) { // also error.framingError, error.commandInvalid
                             // etc...
    }
  }
  Serial.println("Result:" + String(degs));
  delay(1);
}