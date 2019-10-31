
#include "MeMCore.h"

#define 90_DEGREES = 100 // time taken to turn 90 degrees
#define MOTOR_SPEED = 100 // use either this or line below
uint8_t motorSpeed = 100;

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
  if (digitalRead(S1) == HIGH) { // 100-300 Hz detected
    turn(1);
  }
  else if (digitalRead(S2) == HIGH) { // > 3000 Hz detected
    turn(2);
  }
  else {  // no sound at checkpoint - reached the end
    play_victory();
  }
}

// detects what colour paper based on wavelength of light reflected and executes action
void colour_sensor() {
  switch(light_value) {
    case RED: turn(1); break;
    case GREEN: turn(2); break;
    case YELLOW: turn(5); break;
    case PURPLE: turn(3); break;
    case LIGHT_BLUE: turn(4); break;
    case BLACK: frequency_sensor(); break;
    default: break;
}

// turns in desired direction
void turn(int direction) {
  switch(direction) {
    case 1: motor1.run(motorSpeed); // turns left
            motor2.run(motorSpeed);
            delay(90_DEGREES); 
            motor1.stop();
            motor2.stop();
            break;
    case 2: motor1.run(-motorSpeed); // turns right
            motor2.run(-motorSpeed);
            delay(90_DEGREES); 
            motor1.stop();
            motor2.stop();
    case 3: motor1.run(motorSpeed); // first left turn (turn left 2 grids)
            motor2.run(motorSpeed);
            delay(90_DEGREES); 
            motor1.run(-motorSpeed); // moves forward
            motor2.run(motorSpeed);
            delay(ONE_GRID);
            motor1.run(motorSpeed); // second left turn
            motor2.run(motorSpeed);
            delay(90_DEGREES); 
            motor1.stop();
            motor2.stop();
            break;
    case 4: motor1.run(-motorSpeed); // first right turn (turn right 2 grids)
            motor2.run(-motorSpeed);
            delay(90_degrees); 
            motor1.run(-motorSpeed); // moves forward
            motor2.run(motorSpeed);
            delay(one_grid);
            motor1.run(-motorSpeed); // second right turn
            motor2.run(-motorSpeed);
            delay(90_DEGREES); 
            motor1.stop();
            motor2.stop();
            break;
    case 5: motor1.run(-motorSpeed); // turn 180
            motor2.run(-motorSpeed);
            delay(2*90_DEGREES); 
            motor1.stop();
            motor2.stop();
            break;
    default: break;
  }
}
*/
