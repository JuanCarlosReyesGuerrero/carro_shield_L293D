//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library//-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing//
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> ManageLibrary
//search and download library


#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR12_1KHZ);

Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

int motorSpeed = 200;
int motorOffset = 10;
int turnSpeed = 40;

int distanceMin = 30;
int stopDist = 20;

byte alto = 250;
byte bajo = 200;

void setup() {

  Serial.begin(9600);

  //myservo.attach(9);
  //myservo.write(0);
  //delay(2000);
  //distance = readDistance();
  //delay(100);
  //distance = readDistance();
  //delay(100);
  //distance = readDistance();
  //delay(100);
  //distance = readDistance();
  //delay(100);

  motor2.setSpeed(motorSpeed + motorOffset);
  motor3.setSpeed(motorSpeed);

  motor2.run(RELEASE);
  motor3.run(RELEASE);

  //Serial.println("Avanza 1");
  myservo.attach(9);

}

void loop()
{

  //int distanceR = 0;
  //int distanceL =  0;
  //delay(40);

  myservo.write(90);
  delay(750);

  int distance = readDistance();

  if (distance >= distanceMin)
  {
    moveForward();
    //Serial.println("Avanza");
  }

  while (distance >= stopDist)
  {
    distance = readDistance();
    delay(250);
  }

  moveStop();
  //Serial.println("Para");

  int turnDir = checkDirection();

  Serial.print(turnDir);

  switch (turnDir)
  {
    case 0:
      //turnLeft(400);
      Serial.println("Gira izquierda");
      break;
    case 1:
      turnLeft(700);
      //Serial.println("Gira izquierda");
      break;
    case 2:
      turnRight(700);
      Serial.println("Gira derecha");
      break;
  }

  //int a = readDistance();
  //Serial.println(a);

}

int lookRight()
{
  myservo.write(30);
  delay(500);
  int distance = readDistance();
  delay(100);
  myservo.write(90);
  return distance;
}

int lookLeft()
{
  myservo.write(150);
  delay(500);
  int distance = readDistance();
  delay(100);
  myservo.write(90);
  return distance;
  delay(100);
}

int readDistance() {

  delayMicroseconds(10);

  int cm = sonar.ping_cm();

  //Serial.println(cm);

  return cm;
}

void moveStop() {

  motor2.run(RELEASE);
  motor3.run(RELEASE);

}

void moveForward()
{
  motor2.run(FORWARD);
  motor3.run(FORWARD);
}



void turnRight(int duration)
{
  motor2.setSpeed(motorSpeed + turnSpeed);
  motor3.setSpeed(motorSpeed + motorOffset + turnSpeed);

  motor2.run(FORWARD);
  motor3.run(BACKWARD);

  delay(duration);

  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed + motorOffset);

  motor2.run(RELEASE);
  motor3.run(RELEASE);
}

void turnLeft(int duration)
{
  motor2.setSpeed(motorSpeed + motorOffset + turnSpeed);
  motor3.setSpeed(motorSpeed + turnSpeed);

  motor2.run(BACKWARD);
  motor3.run(FORWARD);

  delay(duration);

  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed + motorOffset);

  motor2.run(RELEASE);
  motor3.run(RELEASE);
}



int checkDirection()
{
  /*
    int distances [2] = {0, 0};
    int turnDir = 1;

    myservo.write(180);

    delay(500);
    distances [0] = readDistance();

    myservo.write(0);

    delay(1000);

    distances [1] = readDistance();

    Serial.println(distances [0]);
    Serial.println(distances [1]);

    if (distances[0] >= distanceMin && distances[1] >= distanceMin)
    turnDir = 0;
    else if (distances[0] <= stopDist && distances[1] <= stopDist)
    turnDir = 1;
    else if (distances[0] >= distances[1])
    turnDir = 0;
    else if (distances[0] < distances[1])
    turnDir = 2;
    return turnDir;
  */

  int distances [2] = {0, 0};
  int turnDir = 1;

  myservo.write(180);
  delay(1000);
  distances [0] = readDistance();

  myservo.write(0);
  delay(1000);
  distances [1] = readDistance();

  //Serial.println(distances [0]);
  //Serial.println(distances [1]);

  if (distances[0] >= distanceMin)
    turnDir = 1;
  else if (distances[0] <= distances[1])
    turnDir = 2;

  return turnDir;

}





void accelerate()
{
  for (int i = 0; i < motorSpeed; i++)
  {
    motor2.setSpeed(i);
    motor3.setSpeed(i + motorOffset);

    delay(10);
  }
}

void decelerate()
{
  for (int i = motorSpeed; i != 0; i--)
  {
    motor2.setSpeed(i);
    motor3.setSpeed(i + motorOffset);

    delay(10);
  }
}
