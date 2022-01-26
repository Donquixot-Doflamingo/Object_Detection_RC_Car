#include <IRremote.h>
int RECV_PIN = 11;          // Output pin of TSOP sensor
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{

Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(6,INPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}
void fwd()          // function to move forward
{
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(12,LOW);
   digitalWrite(13,HIGH);
}
void back()        // function to move backward
{
  digitalWrite(8,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
}
void left()        // function to turn left
{
  digitalWrite(7,HIGH);
  digitalWrite(13,LOW);
  digitalWrite(8,LOW);
  digitalWrite(12,LOW);
}
void right()        // function to turn right
{
  digitalWrite(7,LOW);
  digitalWrite(13,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(12,LOW);
}
void stp()        // function to stop
{
  digitalWrite(7,LOW);
  digitalWrite(13,LOW);
  digitalWrite(8,LOW);
  digitalWrite(12,LOW);
}
void loop()
{
   if (irrecv.decode(&results))
  {
    Serial.println(results.value,HEX);
   if((results.value)==0x1FEB04F)
     {
      stp();
     }
   if ((results.value)==0x1FE50AF)
       {
       fwd(); 
       }
  if ((results.value)==0x1FED827)
       {
       back(); 
       }
  if ((results.value)==0x1FEF807)
       {
       left(); 
        }
  if ((results.value)==0x1FE30CF)
       {
       right(); 
       }
irrecv.resume();   // Receive the next value

}
}    
