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
char /*frase[40],*/ get_char, frase_i2c_master[10];
unsigned int val[2], val_sens[8];

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

int decode_i2c_info(char * frase_i2c_master, unsigned int * val, int len){
  if(len != 8){
    return -100;
  } else {
    sscanf(frase_i2c_master,"#%2x %2x %2x$", &val[0], &val[1], &val[2]);
    // Serial.print("val_1: ");
    // Serial.println(val[0]);
    // Serial.print("val_2: ");
    // Serial.println(val[1]);
    if(val[0]!=i2c_slave_id && (val[2]==1 || val[2]==2)) return -101;
    else if(val[0]==i2c_slave_id && (val[2]!=1 && val[2]!=2)) return -102;
    else if(val[0]!=i2c_slave_id && val[2]!=1 && val[2]!=2) return -103;
    else if(val[2]==1) return 0;
    else if(val[2]==2) return 1;
  }
  return -500;
}

int peak_command_msgs(char * resposta_ver, char * resposta, int * frase_valida, int * nsens, int * ready_check){
  char read_char;
  int j=0, waiting_1st=0;
  while(read_char != '$' && mySerial.available()>0){
    read_char = mySerial.read();
    if (read_char == '#'){
        resposta[j] = read_char;
        j++;
        waiting_1st=0;
    } else if ((waiting_1st==0) && ((read_char >= '0' && read_char <= '9') || (read_char >= 'A' && read_char <= 'F') || (read_char >= 'a' && read_char <= 'f') || read_char == '#' || read_char == '$')){ //mudei de 'z' para 'f'     
        //Serial.print("Hello there :)");
        resposta[j] = read_char;
        if (read_char == '$'){
          Serial.print("J: ");
          Serial.println(j);
          Serial.print("Read char: ");
          Serial.println(read_char);
          if(j != 9){
            return -100;
          } else {
            sscanf(resposta,"#%2x %2x %2x$", &val[0], &val[1], &val[2]);
            // Serial.print("val_1: ");
            // Serial.println(val[0]);
            // Serial.print("val_2: ");
            // Serial.println(val[1]);
            if(val[0]!=i2c_slave_id && (val[2]==1 || val[2]==2)) return -101;
            else if(val[0]==i2c_slave_id && (val[2]!=1 && val[2]!=2)) return -102;
            else if(val[0]!=i2c_slave_id && val[2]!=1 && val[2]!=2) return -103;
            else if(val[2]==1) return 0;
            else if(val[2]==2) return 1;
              
            return -500;
/*
VER O QUE FAZER COM ESTA PARTE DO CODIGO... BASICAMENTE QUERO VERIFICAR SE HA
MSG PARA SEREM RECEBIDAS ANTES DE ENVIAR OUTRA, E CASO HAJA, RECEBO A MSG E 
VERIFICO SE ESTÁ FIXE
*/
            waiting_1st=1;  
            *nsens=0;
            *frase_valida=0;
            Serial.println("ERRO NA LEITURA DE SENSORES... VERIFICAR SE ESTÁ A SER ENVIADA A LEITURA NO FORMATO %4X"); 
          }
          *nsens=j+1;
          j=0;
          *frase_valida=1;
        } else {
          j++;
        }
    } else {
      Serial.println("WAITING FOR #..."); 
      waiting_1st=1;
      j=0;
      *nsens=0;
      *frase_valida=0;
      i++;
      if (i==5){
        *ready_check=0;
        i=0;
      }
    }
  }

  read_char = '(';

  if (*ready_check==1 && *frase_valida==1){
    memcpy(resposta_ver, resposta, *nsens);
    return 1;
  } else if (*ready_check==1 && *frase_valida==0){
    return 0;
  } else if (*ready_check==0){
    return -1;
  } else { 
    return 500;
  }

  return 0;
}

int send_serial(int num_sens, unsigned int * val){
  char frase[40];
  switch(num_sens){
  case 1:
    sprintf(frase, "#%04X$", val[0]);
    if (mySerial){
      Serial.println("mySerial ready!");
      mySerial.write(frase); 
    }
    return 1;
    break;
  case 2:
    sprintf(frase, "#%04X%04X$", val[0], val[1]);
    if (mySerial){
      Serial.println("mySerial ready!");
      mySerial.write(frase); 
    }
    return 2;
    break;
  case 3:
    sprintf(frase, "#%04X%04X%04X$", val[0], val[1], val[2]);
    if (mySerial){
      Serial.println("mySerial ready!");
      mySerial.write(frase); 
    } 
    return 3;
    break;
  case 4:
    sprintf(frase, "#%04X%04X%04X%04X$", val[0], val[1], val[2], val[3]);
    if (mySerial){
      Serial.println("mySerial ready!");
      mySerial.write(frase); 
    }
    return 4;
    break;
  case 5:
    sprintf(frase, "#%04X%04X%04X%04X%04X$", val[0], val[1], val[2], val[3], val[4]);
    if (mySerial){
      Serial.println("mySerial ready!");
      mySerial.write(frase); 
    }
    return 5;
    break;
  case 6:
    sprintf(frase, "#%04X%04X%04X%04X%04X%04X$", val[0], val[1], val[2], val[3], val[4], val[5]);
    if (mySerial){
      Serial.println("mySerial ready!");
      mySerial.write(frase); 
    }   
    return 6;
    break;
  case 7:
    sprintf(frase, "#%04X%04X%04X%04X%04X%04X%04X$", val[0], val[1], val[2], val[3], val[4], val[5], val[6]);
    if (mySerial){
      Serial.println("mySerial ready!");
      mySerial.write(frase); 
    }  
    return 7;
    break;
  case 8:
    sprintf(frase, "#%04X%04X%04X%04X%04X%04X%04X%04X$", val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
    if (mySerial){
      Serial.println("mySerial ready!");
      mySerial.write(frase); 
    }  
    return 8;
    break;
  default:  
    return 0;
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
  
  val_sens[0] = analogRead(sens1);
  val_sens[1] = analogRead(sens2);
  val_sens[2] = analogRead(sens3);
  val_sens[3] = analogRead(sens4);
  val_sens[4] = analogRead(sens5); 
  
  /*
  val1 = 134;
  val2 = 1024;
  val3 = 1;
  val4 = 0;
  val5 = 56;
  */
  Serial.println();
  Serial.println(len);
  //sprintf(frase, "#%04X%04X%04X%04X%04X$", val1, val2, val3, val4, val5);
  //mySerial.write("Hello World!"); 
  //int p = peak_command_msgs();
  int h = send_serial(5, val_sens);

  Serial.print("N. Sens: ");
  Serial.println(h);
  //Serial.print("Frase: ");
  //Serial.println(frase);

  // if (mySerial){
  //   Serial.println("mySerial ready!");
  //   mySerial.write(frase); 
  // }

  Serial.print("TAMANHO DA FRASE I2C: ");
  Serial.println(sizeof(frase_i2c_master));
  Serial.println(frase_i2c_master);
  
  command = decode_i2c_info(frase_i2c_master, val, len);
  Serial.print("Valor retornado por 'decode_i2c_info': ");
  Serial.println(command);

  if(command == -100) Serial.println("ERRO: tamanho da frase recebida inválido");
  else if(command == -101) Serial.println("ERRO: id do slave incorreto");
  else if(command == -102) Serial.println("ERRO: ordens incorretas");
  else if(command == -103) Serial.println("ERRO: id do slave e ordens incorretas");
  else if(command == -500) Serial.println("ERRO: saída inesperada");
  else if(command == 0){
    Serial.println("OFF");
    Serial.print("SENSOR: ");
    Serial.println(val[1]);
    //digitalWrite(val[1], false); //DESCOMENTAR E ACRESCEBTAR VALOR DO PINO
  } else if(command == 1){ 
    Serial.println("ON");
    //digitalWrite(val[1], true); //DESCOMENTAR E ACRESCEBTAR VALOR DO PINO
  }


  // if (strcmp(frase_i2c_master,"#01$")==0){
  //   Serial.println("digitalWrite(qq coisa a LOW)");
  // } else if (strcmp(frase_i2c_master,"#02$")==0){
  //   Serial.println("digitalWrite(qq coisa a HIGH)");
  // } else {
  //   Serial.println("Mensagem desconhecida...");
  // }
if (Wire.available()==0) len=0;

delay(500);
}