#include <IRremote.h>
#include <AFMotor.h> 

AF_DCMotor motor1(1);
AF_DCMotor motor2(4);

IRrecv IR(A5);
decode_results result;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IR.enableIRIn(); // Start the receiver

}

void loop() {
  if (IR.decode())
    {
     Serial.println(result.value, HEX);
     IR.resume(); // Receive the next value
    }
}
