#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num_bytes = 1, contagem = 0, ready_check=0, i=0, j=0, test=0, /*val_1=0, val_2=0, val_3=0, val_4=0, val_5=0,*/ waiting_1st=0, nsens=0, frase_valida=0;
uint16_t val_1=0, val_2=0, val_3=0, val_4=0, val_5=0, val_6=0, val_7=0, val_8=0;
char transf_char, check_char, resposta[40], read_char, resposta_ver[40]; 
char val1[2]="", val2[2]="", val3[2]="", val4[2]="", val5[2]="";
String val_dec;
char output=0;

int initial_verification(){
  while(check_char != '$'){
    Wire.requestFrom(1, 1);
    while (Wire.available()) {
      check_char = Wire.read(); 
      Serial.println(check_char);
    }
  }
  return 1;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  if (ready_check == 1) {
    Serial.println();
    Serial.println("VERIFICADO");
    while(read_char != '$'){
      Wire.requestFrom(1, 1);
      while (Wire.available()) {
        read_char = Wire.read();
        if (read_char == '#'){
          resposta[j] = read_char;
          j++;
          waiting_1st=0;
        } else if ((waiting_1st==0) && ((read_char >= '0' && read_char <= '9') || (read_char >= 'A' && read_char <= 'F') || (read_char >= 'a' && read_char <= 'f') || read_char == '#' || read_char == '$')){ //mudei de 'z' para 'f'     
          //Serial.print("Hello there :)");
          resposta[j] = read_char;
          if (/*j==12 ||*/ read_char == '$'){ //eliminar "==12", testar isto
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
        //resposta_2[i] = read_char;
        //Serial.print(read_char);
        //Serial.println();
        //Serial.print(resposta[0]);
        //Serial.println();        
        //Serial.print(resposta[j]);
      }
      /*if (j==0){
        i=0;
      } else { 
        i++;
      }*/
    }
  } else {
    ready_check = initial_verification();
  }

  //if (sizeof(resposta)<12) Serial.print("ANSWER IS TOO SHORT!"); 
  //else Serial.print("ANSWER HAS THE RIGHT SIZE!!");
  
  Serial.println();
  Serial.print("Ready_check:");
  Serial.print(ready_check);
  Serial.println();
  //Serial.print(" resposta[0]: ");
  //Serial.print(resposta[0]);
  //Serial.println();
  read_char = '(';
  //Serial.println("Hello");
  /*for (int i=1; i <= sizeof(resposta); i++){
    resposta[i-1]=resposta[i];
  }*/
  
  //Serial.println();
  //Serial.print(" resposta[0]: ");
  Serial.print(resposta);
  //Serial.println();
  //Serial.print(resposta);
  
  Serial.println();
  Serial.print(nsens);
  
  Serial.println();
  if (frase_valida==1){
    Serial.print("FRASE VÁLIDA");
    Serial.println();
    memcpy(resposta_ver, resposta, nsens);
    Serial.print("RESPOSTA VERIFICADA: ");
    Serial.print(resposta_ver);
  } else if (frase_valida==0){
    Serial.print("RESPOSTA INVÁLIDA");
  }
  
  /*
  Serial.println();
  sscanf(resposta,"# %2c %2c %2c %2c %2c $", val1, val2, val3, val4, val5);
  Serial.println();
  Serial.print("val1: ");
  Serial.print(val1);
  Serial.println();
  Serial.print("val2: ");
  Serial.print(val2);
  Serial.println();
  Serial.print("val3: ");
  Serial.print(val3);
  Serial.println();
  Serial.print("val4: ");
  Serial.print(val4);
  Serial.println();
  Serial.print("val5: ");
  Serial.print(val5);
  Serial.println();
  */
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
  
  //Serial.print(resposta);
  //int number = (int)strtol(val[i], NULL, 16); //FUNCIONA -> NÚMEROS EM HEX VOLTAM A SER NÚMEROS EM DEC
  //--FUNCIONA--
  /*
  char output=0;
  if(val[i][0] <= '9' && val[i][0] >= '0') output += val[i][0]-'0';
  if(val[i][0] <= 'f' && val[i][0] >= 'a') output += val[i][0]-'a'+0xA;
  if(val[i][0] <= 'F' && val[i][0] >= 'A') output += val[i][0]-'A'+0xA;
  output *= 0x10;
  if(val[i][1] <= '9' && val[i][1] >= '0') output += val[i][1]-'0';
  if(val[i][1] <= 'f' && val[i][1] >= 'a') output += val[i][1]-'a'+0xA;
  if(val[i][1] <= 'F' && val[i][1] >= 'A') output += val[i][1]-'A'+0xA;
  */
  delay(500);
}
