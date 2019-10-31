
#include "MeMCore.h"
// testing github
// DC motors
MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
// Infrared
MeUltrasonicSensor ultraSensor(PORT_3); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */
// Black line sensor
MeLineFollower lineFinder(PORT_4); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */

uint8_t motorSpeed = 100;

/*
front_ultrasonic();
side_ir();
black_line_sensor();
sound_checker();
frequency_sensor();
colour_sensor();
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorState = lineFinder.readSensors();
  
  while (sensorState == S1_OUT_S2_OUT) {
    sensorState = lineFinder.readSensors();
    switch(sensorState)
    {
      case S1_IN_S2_IN: Serial.println("Sensor 1 and 2 are inside of black line"); break;
      case S1_IN_S2_OUT: Serial.println("Sensor 2 is outside of black line"); break;
      case S1_OUT_S2_IN: Serial.println("Sensor 1 is outside of black line"); break;
      case S1_OUT_S2_OUT: Serial.println("Sensor 1 and 2 are outside of black line"); break;
      default: break;
    }

    if (ultraSensor.distanceCm() < 10) {
      motor1.stop();
      motor2.stop();
    }
    else {
      motor1.run(-motorSpeed); /* value: between -255 and 255. */
      motor2.run(motorSpeed); /* value: between -255 and 255. */
    }
  }
  motor1.stop();
  motor2.stop();
}
