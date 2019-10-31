
#include "MeMCore.h"

// DC motors
MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
// Infrared

// Ultrasonic sensor
MeUltrasonicSensor ultraSensor(PORT_3); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */
// Black line sensor
MeLineFollower lineFinder(PORT_4); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */
// Sound sensor
pinMode(S1, INPUT); // detects 100-300Hz
pinMode(S2, INPUT); // detects > 3000Hz
// Light sensor
MeLightSensor lightSensor(PORT_6);

uint8_t motorSpeed = 100;

/*
void front_ultrasonic();
void side_ir();
void black_line_sensor();

// detects frequency of sound emitted and executes action
void frequency_sensor();
// detects what colour paper based on wavelength of light reflected and executes action
void colour_sensor();
//turns mBot
void turn(int);
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorState = lineFinder.readSensors();
  int colour;
  
  // While not on black line, move forward
  while (sensorState == S1_OUT_S2_OUT) {
    sensorState = lineFinder.readSensors();
    
    // If approaching front wall, stop
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

  colour_sensor();
  
}

/*
// might be built into void loop()
void front_ultrasonic();
void side_ir();
void black_line_sensor();

// detects frequency of sound emitted and executes action
void frequency_sensor() {
  if (digitalRead(S1) == HIGH) {
    turn(1);
  }
  else if (digitalRead(S2) == HIGH) {
    turn(2);
  }
}

// detects what colour paper based on wavelength of light reflected and executes action
void colour_sensor() {
  
}

// turns in desired direction
void turn(int direction) {
  switch(direction) {
    case 1: turn left; break;
    case 2: turn right; break;
    case 3: turn left 2 grids; break;
    case 4: turn right 2 grids; break;
    case 5: turn 180; break;
    default: break;
  }
}
*/
