/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
const int trigPin = A2;             
const int echoPin = A3;
// defines variables
long duration;
int ultra_distance;

int IN1 = 2;
int IN2 = 4;
int IN3 = 5;
int IN4 = 6;
int IN5 = 7;
int IN6 = 8;
int IN7 = 12;   
int IN8 = 13;
int EN1 = 3;
int EN2 = 9;
int EN3 = 10;   
int EN4 = 11;



VL53L0X sensor;

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  ultra_distance = duration * 0.034 / 2;
  int lidar_distance=sensor.readRangeContinuousMillimeters();
  if (ultra_distance>10)
  {
  if (lidar_distance>0 && lidar_distance<50)
  {
    Serial.print(" safe");
    // Rotate the Motor A clockwise
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, 64);
    // Rotate the Motor B clockwise
    digitalWrite(IN3, HIGH);   
    digitalWrite(IN4, LOW);
    analogWrite(EN2, 64);
    // Rotate the Motor C clockwise
    digitalWrite(IN5, LOW);   
    digitalWrite(IN6, HIGH);
    analogWrite(EN3, 64);
    // Rotate the Motor D clockwise
    digitalWrite(IN7, HIGH);   
    digitalWrite(IN8, LOW);
    analogWrite(EN4,64);
  }
  else if (lidar_distance>50 && lidar_distance<100)
  {
    Serial.print(" medium");
    // Rotate the Motor A clockwise
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN1, 45);
    // Rotate the Motor B clockwise
    digitalWrite(IN3, HIGH);   
    digitalWrite(IN4, LOW);
    analogWrite(EN2, 45);
    // Rotate the Motor C clockwise
    digitalWrite(IN5, LOW);   
    digitalWrite(IN6, HIGH);
    analogWrite(EN3, 45);
    // Rotate the Motor D clockwise
    digitalWrite(IN7, HIGH);   
    digitalWrite(IN8, LOW);
    analogWrite(EN4,45);
  }
  else 
  {
    Serial.print(" risk");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);   
    digitalWrite(IN4, LOW);
    digitalWrite(IN5, LOW);
    digitalWrite(IN6, LOW);
    digitalWrite(IN7, LOW);   
    digitalWrite(IN8, LOW);
  } 
  Serial.println();
  delay(1000);
  }
  else
  {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);   
  digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW);   
  digitalWrite(IN8, LOW);
  }
}
