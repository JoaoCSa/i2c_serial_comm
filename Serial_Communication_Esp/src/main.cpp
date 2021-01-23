#include <Arduino.h>
#include <HardwareSerial.h>

#define RXPIN 16
#define TXPIN 17

//HardwareSerial Serial2(2);

/*
Varáveis usadas no código i2c
*/
int num_bytes = 1, contagem = 0, ready_check=0, i=0, j=0, test=0, /*val_1=0, val_2=0, val_3=0, val_4=0, val_5=0,*/ waiting_1st=0, nsens=0, frase_valida=0;
uint16_t val_1=0, val_2=0, val_3=0, val_4=0, val_5=0, val_6=0, val_7=0, val_8=0;
char transf_char, check_char, resposta[40], read_char, resposta_ver[40]; 
char val1[2]="", val2[2]="", val3[2]="", val4[2]="", val5[2]="";
String val_dec;
char output=0;

char msg; //Initialized variable to store recieved data

int initial_verification(){
/*
  while(check_char != '$'){
    Wire.requestFrom(1, 1);
    while (Wire.available()) {
      check_char = Wire.read(); 
      Serial.println(check_char);
    }
  }
*/
  while (check_char != '$' && Serial2.available()>0){
    check_char = Serial2.read();
    Serial.print("check_char: ");
    Serial.println(check_char);
  }

  if (check_char == '$'){ 
    return 1;
  } else if (check_char != '$' && Serial2.available()==0) {
    return 0;
  } else {
    return -1;
  }
}  

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXPIN, TXPIN);
}

void loop() {
 if (ready_check == 1) {
    Serial.println("VERIFICADO");
    while(read_char != '$' && Serial2.available()>0){
      read_char = Serial2.read();
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
            if ((j+1)%2 != 0){
              waiting_1st=1;  
              nsens=0;
              frase_valida=0;
              Serial.println("ERRO NA LEITURA DE SENSORES... VERIFICAR SE ESTÁ A SER ENVIADA A LEITURA NO FORMATO %4X"); 
            }
            nsens=j+1;
            j=0;
            frase_valida=1;
          } else {
            j++;
          }
      } else {
      Serial.println("WAITING FOR #..."); 
      waiting_1st=1;
      j=0;
      nsens=0;
      frase_valida=0;
      //ready_check=0;  //testar isto
      }
    }
  } else {
    ready_check = initial_verification();
    if (ready_check == 1){
      Serial.print("Code: ");
      Serial.println(ready_check);  
    } else {
      Serial.print("Error code: ");
      Serial.println(ready_check);
    }
  }
  
read_char = '(';

if (ready_check==1 && frase_valida==1){
  Serial.println("FRASE VÁLIDA");
  memcpy(resposta_ver, resposta, nsens);
  Serial.print("RESPOSTA VERIFICADA: ");
  Serial.println(resposta_ver);
} else if (ready_check==1 && frase_valida==0){
  Serial.println("RESPOSTA INVÁLIDA");
}

  if (((nsens-2)/4)==8){ //NO CASO DE TER 8 SENSORES
    sscanf(resposta_ver,"# %4x %4x %4x %4X %4x $", &val_1, &val_2, &val_3, &val_4, &val_5, &val_6, &val_7, &val_8);
    Serial.println();
    Serial.print("val_1: ");
    Serial.print(val_1);
    Serial.println();
    Serial.print("val_2: ");
    Serial.print(val_2);
    Serial.println();
    Serial.print("val_3: ");
    Serial.print(val_3);
    Serial.println();
    Serial.print("val_4: ");
    Serial.print(val_4);
    Serial.println();
    Serial.print("val_5: ");
    Serial.print(val_5);
    Serial.println();
    Serial.print("val_6: ");
    Serial.print(val_6);
    Serial.println();
    Serial.println();
    Serial.print("val_7: ");
    Serial.print(val_7);
    Serial.println();
    Serial.print("val_8: ");
    Serial.print(val_8);
    Serial.println();
  }else if (((nsens-2)/4)==7){ //NO CASO DE TER 7 SENSORES
    sscanf(resposta_ver,"# %4x %4x %4x %4X %4x $", &val_1, &val_2, &val_3, &val_4, &val_5, &val_6, &val_7);
    Serial.println();
    Serial.print("val_1: ");
    Serial.print(val_1);
    Serial.println();
    Serial.print("val_2: ");
    Serial.print(val_2);
    Serial.println();
    Serial.print("val_3: ");
    Serial.print(val_3);
    Serial.println();
    Serial.print("val_4: ");
    Serial.print(val_4);
    Serial.println();
    Serial.print("val_5: ");
    Serial.print(val_5);
    Serial.println();
    Serial.println();
    Serial.print("val_6: ");
    Serial.print(val_6);
    Serial.println();
    Serial.println();
    Serial.print("val_7: ");
    Serial.print(val_7);
    Serial.println();
  }else if (((nsens-2)/4)==6){ //NO CASO DE TER 6 SENSORES
    sscanf(resposta_ver,"# %4x %4x %4x %4x %4x %4x $", &val_1, &val_2, &val_3, &val_4, &val_5, &val_6);
    Serial.println();
    Serial.print("val_1: ");
    Serial.print(val_1);
    Serial.println();
    Serial.print("val_2: ");
    Serial.print(val_2);
    Serial.println();
    Serial.print("val_3: ");
    Serial.print(val_3);
    Serial.println();
    Serial.print("val_4: ");
    Serial.print(val_4);
    Serial.println();
    Serial.print("val_5: ");
    Serial.print(val_5);
    Serial.println();
    Serial.print("val_6: ");
    Serial.print(val_6);
    Serial.println();
  }else if (((nsens-2)/4)==5){ //NO CASO DE TER 5 SENSORES
    sscanf(resposta_ver,"# %4x %4x %4x %4X %4x $", &val_1, &val_2, &val_3, &val_4, &val_5);
    Serial.println();
    Serial.print("val_1: ");
    Serial.print(val_1);
    Serial.println();
    Serial.print("val_2: ");
    Serial.print(val_2);
    Serial.println();
    Serial.print("val_3: ");
    Serial.print(val_3);
    Serial.println();
    Serial.print("val_4: ");
    Serial.print(val_4);
    Serial.println();
    Serial.print("val_5: ");
    Serial.print(val_5);
    Serial.println();
  } else if (((nsens-2)/4)==4){ //NO CASO DE TER 4 SENSORES
    sscanf(resposta_ver,"# %4x %4x %4x %4x $", &val_1, &val_2, &val_3, &val_4);
    Serial.println();
    Serial.print("val_1: ");
    Serial.print(val_1);
    Serial.println();
    Serial.print("val_2: ");
    Serial.print(val_2);
    Serial.println();
    Serial.print("val_3: ");
    Serial.print(val_3);
    Serial.println();
    Serial.print("val_4: ");
    Serial.print(val_4);
    Serial.println();
  } else if (((nsens-2)/4)==3){ //NO CASO DE TER 3 SENSORES
    sscanf(resposta_ver,"# %4x %4x %4x $", &val_1, &val_2, &val_3);
    Serial.println();
    Serial.print("val_1: ");
    Serial.print(val_1);
    Serial.println();
    Serial.print("val_2: ");
    Serial.print(val_2);
    Serial.println();
    Serial.print("val_3: ");
    Serial.print(val_3);
    Serial.println();
  } else if (((nsens-2)/4)==2){ //NO CASO DE TER 2 SENSORES
    sscanf(resposta_ver,"# %4x %4x $", &val_1, &val_2);
    Serial.println();
    Serial.print("val_1: ");
    Serial.print(val_1);
    Serial.println();
    Serial.print("val_2: ");
    Serial.print(val_2);
    Serial.println();
  } else if (((nsens-2)/4)==1){ //NO CASO DE TER 1 SENSORES
    sscanf(resposta_ver,"# %4x $", &val_1);
    Serial.println();
    Serial.print("val_1: ");
    Serial.print(val_1);
    Serial.println();
  } else {
    Serial.println();
    Serial.print("NÚMERO DE SENSORES INVÁLIDO");
    Serial.println();
  }


delay(500);
}



/*------ GRAVEYARD ------*/

/*
if (Serial2.available()>0){
  Serial.println("Serial available: ");
  Serial.print(Serial2.available());
} else if (!Serial2.available()){
  Serial.println("No messages :'(");
}
*/