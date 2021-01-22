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
} 

void loop()
{
  if (mySerial.availableForWrite() != 0){
    mySerial.write("Hello World!");
    Serial.println("Message sent :)");
  } else {
    Serial.println("I don't have any friends :(");
    mySerial.write("Hello World!");
  } 
}