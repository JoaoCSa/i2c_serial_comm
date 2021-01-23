#include <Arduino.h>
#include <SoftwareSerial.h>
/*
RX is digital pin 2 (connect to TX of other device)
TX is digital pin 3 (connect to RX of other device)
*/

SoftwareSerial mySerial(2, 3); // RX, TX
 
int sens1 = A0, sens2 = A1, sens3 = A2, sens4 = A3, sens5 = A6, i=0, t=0;
uint16_t val1=0, val2=0, val3=0, val4=0, val5=0;
char frase[40];

void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(5, OUTPUT);
} 

void loop()
{
  /*
  val1 = analogRead(sens1);
  val2 = analogRead(sens2);
  val3 = analogRead(sens3);
  val4 = analogRead(sens4);
  val5 = analogRead(sens5); 
  */

  val1 = 134;
  val2 = 1024;
  val3 = 1;
  val4 = 0;
  val5 = 56;
    
  sprintf(frase, "#%04X%04X%04X%04X%04X$", val1, val2, val3, val4, val5);
  //mySerial.write("Hello World!"); 
  
  Serial.print("Frase: ");
  Serial.println(frase);

  if (mySerial){
    Serial.println("mySerial ready!");
    mySerial.write(frase); 
  }

delay(500);
}