#include <Arduino.h>
#include <HardwareSerial.h>

#define RXPIN 16
#define TXPIN 17

//HardwareSerial Serial2(2);

/*
Varáveis usadas no código i2c
*/
int ready_check=0, i=0, j=0, waiting_1st=0, nsens=0, frase_valida=0, comm_result=0;
unsigned int val[9];
char check_char, resposta[40], read_char, resposta_ver[40]; 

int initial_verification(){
  while (check_char != '$' && Serial2.available()>0){
    check_char = Serial2.read();
    Serial.print("check_char: ");
    Serial.println(check_char);
  }

  if (check_char == '$'){ 
    check_char = '(';
    return 1;
  } else if (check_char != '$' && Serial2.available()==0) {
    return 0;
  } else {
    return -1;
  }
}  

int decode_info(char * frase, unsigned int * val, int nsens, int frase_valida){ //Dá return ao número de sensores lidos

  Serial.print("FRASE QUE CHEGA A DECODE_INFO: ");
  Serial.println(frase);
 
  if (frase_valida == 1){
    if (((nsens-2)/4)==8){ //NO CASO DE TER 8 SENSORES
      sscanf(resposta_ver,"# %4x %4x %4x %4X %4x %4x %4x %4x $", &val[0], &val[1], &val[2], &val[3], &val[4], &val[5], &val[6], &val[7]);
      Serial.print("val_1: ");
      Serial.println(val[0]);
      Serial.print("val_2: ");
      Serial.println(val[1]);
      Serial.print("val_3: ");
      Serial.println(val[2]);
      Serial.print("val_4: ");
      Serial.println(val[3]);
      Serial.print("val_5: ");
      Serial.println(val[4]);
      Serial.print("val_6: ");
      Serial.println(val[5]);
      Serial.print("val_7: ");
      Serial.println(val[6]);
      Serial.print("val_8: ");
      Serial.println(val[7]);
      return 8;
    }else if (((nsens-2)/4)==7){ //NO CASO DE TER 7 SENSORES
      sscanf(resposta_ver,"# %4x %4x %4x %4X %4x %4x %4x $", &val[0], &val[1], &val[2], &val[3], &val[4], &val[5], &val[6]);
      Serial.print("val_1: ");
      Serial.println(val[0]);
      Serial.print("val_2: ");
      Serial.println(val[1]);
      Serial.print("val_3: ");
      Serial.println(val[2]);
      Serial.print("val_4: ");
      Serial.println(val[3]);
      Serial.print("val_5: ");
      Serial.println(val[4]);
      Serial.print("val_6: ");
      Serial.println(val[5]);
      Serial.print("val_7: ");
      Serial.println(val[6]);
      return 7;
    }else if (((nsens-2)/4)==6){ //NO CASO DE TER 6 SENSORES
      sscanf(resposta_ver,"# %4x %4x %4x %4x %4x %4x $", &val[0], &val[1], &val[2], &val[3], &val[4], &val[5]);
      Serial.print("val_1: ");
      Serial.println(val[0]);
      Serial.print("val_2: ");
      Serial.println(val[1]);
      Serial.print("val_3: ");
      Serial.println(val[2]);
      Serial.print("val_4: ");
      Serial.println(val[3]);
      Serial.print("val_5: ");
      Serial.println(val[4]);
      Serial.print("val_6: ");
      Serial.println(val[5]);
      return 6;
    }else if (((nsens-2)/4)==5){ //NO CASO DE TER 5 SENSORES
      sscanf(resposta_ver,"# %4x %4x %4x %4X %4x $", &val[0], &val[1], &val[2], &val[3], &val[4]);
      Serial.print("val_1: ");
      Serial.println(val[0]);
      Serial.print("val_2: ");
      Serial.println(val[1]);
      Serial.print("val_3: ");
      Serial.println(val[2]);
      Serial.print("val_4: ");
      Serial.println(val[3]);
      Serial.print("val_5: ");
      Serial.println(val[4]);
      return 5;
    } else if (((nsens-2)/4)==4){ //NO CASO DE TER 4 SENSORES
      sscanf(resposta_ver,"# %4x %4x %4x %4x $", &val[0], &val[1], &val[2], &val[3]);
      Serial.print("val_1: ");
      Serial.println(val[0]);
      Serial.print("val_2: ");
      Serial.println(val[1]);
      Serial.print("val_3: ");
      Serial.println(val[2]);
      Serial.print("val_4: ");
      Serial.println(val[3]);
      return 4;
    } else if (((nsens-2)/4)==3){ //NO CASO DE TER 3 SENSORES
      sscanf(resposta_ver,"# %4x %4x %4x $", &val[0], &val[1], &val[2]);
      Serial.print("val_1: ");
      Serial.println(val[0]);
      Serial.print("val_2: ");
      Serial.println(val[1]);
      Serial.print("val_3: ");
      Serial.println(val[2]);
      return 3;
    } else if (((nsens-2)/4)==2){ //NO CASO DE TER 2 SENSORES
      sscanf(resposta_ver,"# %4x %4x $", &val[0], &val[1]);
      Serial.print("val_1: ");
      Serial.println(val[0]);
      Serial.print("val_2: ");
      Serial.println(val[1]);
      return 2;
    } else if (((nsens-2)/4)==1){ //NO CASO DE TER 1 SENSORES
      sscanf(resposta_ver,"# %4x $", &val[0]);
      Serial.print("val_1: ");
      Serial.println(val[0]);
      return 1;
    } else {
      Serial.println("NÚMERO DE SENSORES INVÁLIDO");
      return 0; //Numero de sensores invalido
    }
  } else {
    return -1; //Frase inválida
  }

}

int read_serial_communication(){
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
            Serial.print("Read char: ");
            Serial.println(read_char);
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
        i++;
        if (i==5){
          ready_check=0;
          i=0;
        }
      }
    }

  read_char = '(';

  if (ready_check==1 && frase_valida==1){
    memcpy(resposta_ver, resposta, nsens);
    return 1;
  } else if (ready_check==1 && frase_valida==0){
    return 0;
  } else if (ready_check==0){
    return -1;
  } else { 
    return 500;
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXPIN, TXPIN);
}

void loop() {
  if (ready_check == 1) {
    Serial.println("VERIFICADO");
    comm_result = read_serial_communication();
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
  if (comm_result==1){
    Serial.println("FRASE VÁLIDA");
    Serial.print("RESPOSTA VERIFICADA: ");
    Serial.println(resposta_ver);
  } else if (comm_result==0){
    Serial.println("RESPOSTA INVÁLIDA");
  } else if (comm_result==-1){
    Serial.println("REVERIFICAÇÃO NECESSÁRIA");
  } else if (comm_result==500){
    Serial.println("ERRO DESCONHECIDO...");
  }
  
  Serial.print("Resposta guardada: ");
  Serial.println(resposta);
  
  Serial.print("Numero de bytes: ");
  Serial.println(nsens);

  int n = decode_info(resposta_ver, val, nsens, frase_valida);

  Serial.print("NUMERO DE SENSORES: ");
  Serial.println(n);


delay(500);
}
