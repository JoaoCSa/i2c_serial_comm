#include <Arduino.h>
#include <HardwareSerial.h>
int val=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //pinMode(4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   
    // read the incoming byte:
    val = Serial.read();
    // say what you got:
    Serial.println(val, DEC);
  /*
  val = digitalRead(4);
  Serial.println(val);
  */
}