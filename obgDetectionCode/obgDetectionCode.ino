#include <IRremote.h>

#include "AFMotor.h"
#include <Servo.h>

#define RECV_PIN A3 // recive pin
#define echopin A4 // echo pin
#define trigpin A5// Trigger pin

Servo myservo;

const int MOTOR_2 = 2; 
const int MOTOR_4 = 4; 

IRrecv irrecv(RECV_PIN);
decode_results results; 

AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ); // create motor object, 64KHz pwm

//===============================================================================
//  Initialization
//===============================================================================

int distance_L, distance_F, distance_R;
long distance;

int set = 20;

void setup() {
  Serial.begin(9600);           // Initialize serial port
  Serial.println("Start");

  myservo.attach(10);
  myservo.write(90);

  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  
  motor2.setSpeed(180);
  motor4.setSpeed(180);

  irrecv.enableIRIn();   
}
//===============================================================================
//  Main
//=============================================================================== 
void loop() {
 distance_F = data();
 Serial.print("S=");
 Serial.println(distance_F);
  if (distance_F > set){
   Serial.println("Forward");
  motor2.run(FORWARD);  
  motor4.run(FORWARD);
    }
    else{hc_sr4();}

    if (irrecv.decode())// Returns 0 if no data ready, 1 if data ready 
          // Results of decoding are stored in result.value     
    {
       Serial.println(" ");     
       Serial.print("Code: ");     
       Serial.println(results.value); //prints the value a a button press     
       Serial.println(" ");     
       irrecv.resume(); // Restart the ISR state machine and Receive the next value
    }


long data(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  distance = pulseIn (echopin, HIGH);
  return distance / 29 / 2;
}


void compareDistance(){
  if (distance_L > distance_R){
  motor2.run(BACKWARD);
  motor4.run(FORWARD); 
    delay(350);
  }
  else if (distance_R > distance_L){
  motor2.run(FORWARD); 
  motor4.run(BACKWARD);
    delay(350);
  }
  else{
  motor2.run(BACKWARD);
  motor4.run(BACKWARD); 
   delay(300);
  motor2.run(BACKWARD);
  motor4.run(FORWARD); 
    delay(500);
  }
}

void hc_sr4(){
    Serial.println("Stop");
    motor2.run(RELEASE);
    motor4.run(RELEASE);
   
    myservo.write(0);
    delay(300);
    distance_R = data();
    delay(100);
    myservo.write(170);
    delay(500);
    distance_L = data();
    delay(100);
    myservo.write(90);
    delay(300);
    compareDistance();
}
