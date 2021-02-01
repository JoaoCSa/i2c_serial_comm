#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define i2c_slave_id 1
/*
RX is digital pin 2 (connect to TX of other device)
TX is digital pin 3 (connect to RX of other device)
*/

SoftwareSerial mySerial(2, 3); // RX, TX
 
int len=0, command=0, sens1 = A0, sens2 = A1, sens3 = A2, sens4 = A3, sens5 = A6, i=0, t=0;
uint16_t val1=0, val2=0, val3=0, val4=0, val5=0;
char frase[40], get_char, frase_i2c_master[10];
unsigned int val[2];

void receiveEvent(int howMany)
{
  if (Wire.available()){ 
    get_char = Wire.read();
    if (get_char == '#'){
      frase_i2c_master[i] = get_char;
      i++;
      while(get_char != '$' && Wire.available()){
        get_char = Wire.read(); // receive byte as a character
        //Serial.print(get_char);         // print the character
        frase_i2c_master[i] = get_char;
        i++;
      }
      i=0;
    }
  }
  len = howMany;
  get_char = '(';
}

int decode_i2c_info(unsigned int * val, int len){
  if(len != 6){
    return -100;
  } else {
    sscanf(frase_i2c_master,"# %2x %2x $", &val[0], &val[1]);
    // Serial.print("val_1: ");
    // Serial.println(val[0]);
    // Serial.print("val_2: ");
    // Serial.println(val[1]);
    if(val[0]!=i2c_slave_id && (val[1]==1 || val[1]==2)) return -101;
    else if(val[0]==i2c_slave_id && (val[1]!=1 && val[1]!=2)) return -102;
    else if(val[0]!=i2c_slave_id && val[1]!=1 && val[1]!=2) return -103;
    else if(val[1]==1) return 0;
    else if(val[1]==2) return 0;
  }
  return -500;
}

void setup()
{
  Serial.begin(115200);
  mySerial.begin(115200);
  Wire.begin(i2c_slave_id);
  Wire.onReceive(receiveEvent); // register event
  //pinMode(5, OUTPUT);
} 

void loop()
{
  
  val1 = analogRead(sens1);
  val2 = analogRead(sens2);
  val3 = analogRead(sens3);
  val4 = analogRead(sens4);
  val5 = analogRead(sens5); 
  
  /*
  val1 = 134;
  val2 = 1024;
  val3 = 1;
  val4 = 0;
  val5 = 56;
  */
  Serial.println();
  Serial.println(len);
  sprintf(frase, "#%04X%04X%04X%04X%04X$", val1, val2, val3, val4, val5);
  //mySerial.write("Hello World!"); 
  
  Serial.print("Frase: ");
  Serial.println(frase);

  if (mySerial){
    Serial.println("mySerial ready!");
    mySerial.write(frase); 
  }

  Serial.print("TAMANHO DA FRASE I2C: ");
  Serial.println(sizeof(frase_i2c_master));
  Serial.println(frase_i2c_master);
  
  command = decode_i2c_info(val, len);
  Serial.print("Valor retornado por 'decode_i2c_info': ");
  Serial.println(command);

  if(command == -100) Serial.println("ERRO: tamanho da frase recebida inválido");
  else if(command == -101) Serial.println("ERRO: id do slave incorreto");
  else if(command == -102) Serial.println("ERRO: ordens incorretas");
  else if(command == -103) Serial.println("ERRO: id do slave e ordens incorretas");
  else if(command == -500) Serial.println("ERRO: saída inesperada");
  else if(command == 0){
    Serial.println("OFF");
    //digitalWrite(,FALSE); //DESCOMENTAR E ACRESCEBTAR VALOR DO PINO
  } else if(command == 1){ 
    Serial.println("ON");
    //digitalWrite(,TRUE); //DESCOMENTAR E ACRESCEBTAR VALOR DO PINO
  }


  // if (strcmp(frase_i2c_master,"#01$")==0){
  //   Serial.println("digitalWrite(qq coisa a LOW)");
  // } else if (strcmp(frase_i2c_master,"#02$")==0){
  //   Serial.println("digitalWrite(qq coisa a HIGH)");
  // } else {
  //   Serial.println("Mensagem desconhecida...");
  // }

delay(500);
}