#pragma once
#include <Arduino.h>
#include <stdlib.h>
//Result write operation
#define RESULT_SUCCEFUL 1
#define RESULT_WARNING 2

#define DEFAULT_PORT_CLK 2
#define DEFAULT_PORT_DO  3
#define DEFAULT_PORT_DI  4
#define DEFAULT_PORT_CS  5
#define DEFAULT_PORT_LED 6
#define DEFAULT_DELAY    1
#define DEFAULT_LED_DELAY 10
#define MAX_TIME_WAIT 2

#define COMMAND_MASK 0b10000000
#define COMMAND_SIZE 8

#define DEFAULT_PREFIX_POSITION         0b00011111
#define DEFAULT_KEY_POSITION            0b00100000
#define DEFAULT_ACCESS_MODE_POSITION    0b00100001

#define COUNT_ACCESS_LEVEL 4
#define ACCESS_LEVEL_ENGINEER       0
#define ACCESS_LEVEL_OPERATOR       1
#define ACCESS_LEVEL_ADMINISTRATOR  2
#define ACCESS_LEVEL_DEVELOPER      3

#define ACCESS_LEVEL_ENGINEER_VALUE         0x50
#define ACCESS_LEVEL_OPERATOR_VALUE         0x54
#define ACCESS_LEVEL_ADMINISTRATOR_VALUE    0x58
#define ACCESS_LEVEL_DEVELOPER_VALUE        0x5c

///////////////////////////////////
//  name:   ERASE ALL            //
//  bits:   1 00 10 XXXX         //
//  clocks: 9                    //
///////////////////////////////////
#define COMMAND_ERAL  0b00100000
///////////////////////////////////
//  name:   ERASE/WRITE DISABLE  //
//  bits:   1 00 00 XXXX         //
//  clocks: 9                    //
///////////////////////////////////
#define COMMAND_EWDS  0b00000000
//////////////////////////////////
//  name:   ERASE/WRITE ENABLE  //
//  bits:   1 00 11 XXXX        //
//  clocks: 9                   //
//////////////////////////////////
#define COMMAND_EWEN  0b00110000
///////////////////////////////////
//  name:   WRITE ALL            //
//  bits:   1 00 01 XXXX D15-D0  //
//  clocks: 25                   //
///////////////////////////////////
#define COMMAND_WRAL  0b00010000
//////////////////////////////////
//  name:   WRITE               //
//  bits:   1 01 A5-A0 D15-D0   //
//  clocks: 25                  //
//////////////////////////////////
#define COMMAND_WRITE 0b01000000
//////////////////////////////////
//  name:   READ                //
//  bits:   1 10 A5-A0          //
//  clocks: 25                  //
//////////////////////////////////
#define COMMAND_READ 0b10000000


typedef struct key_data{
    static const uint8_t COUNT_BYTE = 2;
    uint8_t prefix[COUNT_BYTE] = {0,0};
    uint8_t key[COUNT_BYTE] = {0,0};
    uint8_t access_level[COUNT_BYTE] = {0,0};
} key_data_t;

typedef struct ports_93c46wp{
    int port_DO = DEFAULT_PORT_DO;
    int port_CS = DEFAULT_PORT_CS;
    int port_CLK = DEFAULT_PORT_CLK;
    int port_DI = DEFAULT_PORT_DI;
    int port_LED = DEFAULT_PORT_LED;
    int delay = DEFAULT_DELAY;
} ports_93c46wp_t;

void EEP_init(const ports_93c46wp_t &ports);
void EEP___printCommand(const ports_93c46wp_t &ports, uint8_t **data, int count_words);
void EEP___portReset(const ports_93c46wp_t &ports);
void EEP___printStartCommandBit(const ports_93c46wp_t &ports);
int  EEP___isSuccefulWrite(const ports_93c46wp_t &ports);
int  EEP___executeCommand(const ports_93c46wp_t &ports, uint8_t command);

void EEP_modeEWEnable(const ports_93c46wp_t &ports);
void EEP_modeEWDisable(const ports_93c46wp_t &ports);
void EEP_eraseAll(const ports_93c46wp_t &ports);
key_data_t EEP_readKey(const ports_93c46wp_t &ports);
bool EEP_writeKey(const ports_93c46wp_t &ports, unsigned int prefix, long int key, unsigned int access_mode);
bool EEP_isWorkKey(const ports_93c46wp_t &ports);
bool EEP_checkWriteKey(const ports_93c46wp_t &ports, uint8_t prefix, int key, uint8_t access_mode);