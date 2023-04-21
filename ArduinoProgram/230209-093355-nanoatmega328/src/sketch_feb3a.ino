#include <Arduino.h>
#include "source/EEPROM_93C46WP.hpp"
#include <time.h>

int port_DO = 3;
int port_CS = 5;
int port_CLK = 2;
int port_DI = 4;
int port_led = 6;

int DELAY = 1;

int key_0 = 48;
int key_1 = 49;
int key_2 = 50;
int key_3 = 51;
int key_4 = 52;
int key_5 = 53;
int key_6 = 54;
int key_7 = 55;
int key_8 = 56;
int key_9 = 57;
int key_enter = 10;
int key_end = 63;

ports_93c46wp_t ports;

String readSerialInt(){
  String result = "";
  int temp;
  while(1){
    //Serial.println(Serial.peek());
      //delay(200);
    if(Serial.peek() != key_end){
      temp = Serial.read()-key_0;
      if(temp >= 0 && temp <= 9){
        result += temp;
        
      }
    }
    else{
      Serial.read();
      break;
    }
  }
  return result;
}

void setup() {
  srand(time(NULL));
  ports.port_DO = port_DO;
  ports.port_DI = port_DI;
  ports.port_CLK = port_CLK;
  ports.port_CS = port_CS;
  ports.port_LED = port_led;
  ports.delay = DELAY;

  EEP_init(ports);

  Serial.begin(9600);
}

void loop() {
/*
  while(1){
    int i = Serial.read();
    if(i != -1){
      Serial.println(i);
    }
  }*/

  String message;  
  while(1){
    //message = "Enter the number of the operation to be performed";
    //Serial.println(message);

    //message = "1. Write key\n";
    //message += "2. Read key\n";
    //message += "3. Check work key\n";
    //message += "4. Clear key\n";
    //message = "Input: \n";
    //Serial.print(message);

    int variant = -1;
    while(variant == -1){
      variant = Serial.read();
      delay(10);
    }
    //Serial.println(variant-key_0);

    if(variant == key_1){
      long int prefix = 0, key = 0, access_mode = 0;
      String temp;
      //message = "Write Key:\n";
      message = "Key data | ";
      Serial.print(message);

      Serial.print("Prefix: ");

      temp = readSerialInt();
      prefix = temp.toInt();
      Serial.print(prefix);
    
      Serial.print(" || Key: ");

      temp = readSerialInt();
      key = temp.toInt();
      Serial.print(key);

      Serial.print(" || Access_mode: ");
      temp = readSerialInt();
      access_mode = temp.toInt();
      Serial.println(access_mode);

      if(EEP_writeKey(ports,prefix,key,access_mode)){
        Serial.println("Operation write: Succeful");
      }
      else{
        Serial.println("Operation write: ACCESS DENITED");
      }
      Serial.print("\n");
    }
    else if( variant == key_2){
      key_data_t result = EEP_readKey(ports);
      Serial.print("Result read\n");
      Serial.print("Prefix: ");
      Serial.print((int)result.prefix[0], DEC);
      Serial.print(" | Key: ");
      Serial.print(((unsigned int)result.key[0] << 8) | (unsigned int)result.key[1], DEC);
      
      Serial.print(" | Access_mode: ");
      switch((int)result.access_level[0]){
        case ACCESS_LEVEL_ENGINEER_VALUE:
          Serial.println("Engineer (0)");
        break;
        case ACCESS_LEVEL_OPERATOR_VALUE:
          Serial.println("Operator (1)");
        break;
        case ACCESS_LEVEL_ADMINISTRATOR_VALUE:
          Serial.println("Administrator (2)");
        break;
        case ACCESS_LEVEL_DEVELOPER_VALUE:
          Serial.println("Developer (3)");
        break;
        default:
          Serial.println("None");
        break;
      }
      Serial.print("\n");
    }
    else if( variant == key_3){
      message = "Result check: ";
      
      if(EEP_isWorkKey(ports)){
        message += "Succeful\n";
      }
      else{
        message += "ACCESS DENITED\n";
      }
      Serial.println(message);
    }
    else if(variant == key_4){
      //clear
      EEP_eraseAll(ports);
      Serial.print("Clear succeful\n\n");
    }
    //delay(2000);
  }
}
