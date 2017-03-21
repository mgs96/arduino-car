/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 Red POS to Arduino pin 11
 Green POS to Arduino pin 10
 560 ohm resistor to both LED NEG and GRD power rail
 More info at: http://goo.gl/kJ8Gl
 Original code improvements to the Ping sketch sourced from Trollmaker.com
 Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
 */
#include <Servo.h>
Servo myServo;
#define trigPin 13
#define echoPin 12
#define controlPin1_b1 8
#define controlPin2_b1 9
#define controlPin3_b1 6
#define controlPin4_b1 7
#define controlPin1_b2 4
#define controlPin2_b2 5
#define controlPin3_b2 2
#define controlPin4_b2 3
int sensorA0 = A0;//a0
int sensorA1 = A1;//a1
int sensorA2 = A2;//a2
int sensorA3 = A3;//a3
int Vsensor0 = 0;
int Vsensor1 = 0;
int Vsensor2 = 0;
int Vsensor3 = 0;
int val;
int angle;
int MasterSlave = 0; //Master = 0 / Slave = 1

#define led 11
#define led2 10

void setup() {
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(controlPin1_b1, INPUT);
  pinMode(controlPin2_b1, INPUT);
  pinMode(controlPin3_b1, INPUT);
  pinMode(controlPin4_b1, INPUT);
  pinMode(controlPin1_b2, INPUT);
  pinMode(controlPin2_b2, INPUT);
  pinMode(controlPin3_b2, INPUT);
  pinMode(controlPin4_b2, INPUT);
  Serial.begin (9600);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  myServo.attach(11);
}

void loop() {
  //Ligth sensors read
  Vsensor0 = analogRead(sensorA0);
  delay(5);
  Vsensor1 = analogRead(sensorA1);
  delay(5);
  Vsensor2 = analogRead(sensorA2);
  delay(5);
  Vsensor3 = analogRead(sensorA3);}
  //Ligth sensors read END
  //Ultrasound sensor read
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //Ultrasound sensor read END
  distance = (duration/2) / 29.1;
  if (distance < 4) {  // This is where the LED On/Off happens
    //Here we should turn off the dcMotors
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
  }
  else {
    //Here we should turn on the dcMotors
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);

    if(Vsensor0>Vsensor1 && Vsensor0>Vsensor2 && Vsensor0>Vsensor3){
      myServo.write(135);
    }
    if((Vsensor1>Vsensor0 && Vsensor1>Vsensor2 && Vsensor1>Vsensor3)||(Vsensor2>Vsensor0 && Vsensor2>Vsensor1 && Vsensor2>Vsensor3)){
      myServo.write(90);
    }
    if(Vsensor3>Vsensor0 && Vsensor3>Vsensor1 && Vsensor3>Vsensor2){
      myServo.write(45);
    }
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
