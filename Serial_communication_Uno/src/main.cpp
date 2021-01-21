#include <Arduino.h>

char mystr[10]; //Initialized variable to store recieved data

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  Serial1.readBytes(mystr,5); //Read the serial data and store in var
  Serial.println(mystr); //Print data on Serial Monitor
  delay(1000);
}