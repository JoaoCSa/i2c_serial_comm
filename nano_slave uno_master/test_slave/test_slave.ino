#include <Wire.h>

int sens1 = A0, sens2 = A1, sens3 = A2, sens4 = A3, sens5 = A6, i=0, t=0;
uint16_t val1=0, val2=0, val3=0, val4=0, val5=0;
char frase[40]; 

void requestEvent(){
  Wire.write(frase[i]);
  //Serial.print(" ");
  //Serial.print(frase[i]);
  //Serial.print(" ");
  //Serial.print(i);
  //Serial.print(" ");
  if (frase[i] == '$'){
    i=0;
  } else {
    i++;  
  } 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(1);
  Wire.onRequest(requestEvent);
}

void loop() {
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

  Serial.print(" Frase: ");
  Serial.print(frase);
  //Serial.print("Frase[0]: ");
  //Serial.print(frase[0]);
  
  Serial.println();
}
