#include <Arduino.h>
#include <SoftwareSerial.h>
/*
RX is digital pin 2 (connect to TX of other device)
TX is digital pin 3 (connect to RX of other device)
*/

SoftwareSerial mySerial(2, 3); // RX, TX
 
void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(5, OUTPUT);
} 

void loop()
{
    mySerial.write("Hello World!"); 
delay(500);
}