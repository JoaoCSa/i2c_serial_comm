#include <Arduino.h>
#include <HardwareSerial.h>

#define RXPIN 16
#define TXPIN 17

//HardwareSerial Serial2(2);

char msg; //Initialized variable to store recieved data
void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXPIN, TXPIN);
}

void loop() {
  if (Serial2.available()>0){
    msg = Serial2.read();
    Serial.print("Nano says: ");
    Serial.print(msg);
    Serial.println();
  } else if (!Serial2.available()){
    Serial.println("No messages :'(");
  }

}