#include "EEPROM_93C46WP.hpp"

void EEP_init(const ports_93c46wp_t &ports){
    pinMode(ports.port_DO,INPUT);
    pinMode(ports.port_CS, OUTPUT);
    pinMode(ports.port_CLK, OUTPUT);
    pinMode(ports.port_DI, OUTPUT);
    pinMode(ports.port_LED, OUTPUT);
    digitalWrite(ports.port_DI,HIGH);
    delay(ports.delay);
}

void EEP___portReset(const ports_93c46wp_t &ports){
    digitalWrite(ports.port_CS,LOW);
    delay(ports.delay);
    digitalWrite(ports.port_DI,LOW);
    delay(ports.delay);
}

void EEP___printStartCommandBit(const ports_93c46wp_t &ports){
    digitalWrite(ports.port_DI,HIGH);
    delay(ports.delay);
    digitalWrite(ports.port_CLK, HIGH);
    delay(ports.delay);
    digitalWrite(ports.port_CLK, LOW);
    delay(ports.delay);
}

void EEP___printCommand(const ports_93c46wp_t &ports, uint8_t *data, int count_words){  
    for(int i = 0; i < count_words; i++){
        int temp = data[i];
        for(int j = 0; j < COMMAND_SIZE; j++){
            if((temp & COMMAND_MASK) == COMMAND_MASK){
                digitalWrite(ports.port_DI,HIGH);
                delay(ports.delay);
            }
            else{
                digitalWrite(ports.port_DI,LOW);
                delay(ports.delay);
            }
            digitalWrite(ports.port_CLK, HIGH);
            delay(ports.delay);
            digitalWrite(ports.port_CLK, LOW);
            delay(ports.delay);

            temp = temp << 1;
        } 
    }
}

int EEP___isSuccefulWrite(const ports_93c46wp_t &ports){

    digitalWrite(ports.port_CS, HIGH);
    delay(ports.delay);

    int result = 0, time = 0;
    while(result == 0 && time != MAX_TIME_WAIT){
        digitalWrite(ports.port_CLK,HIGH);
        delay(ports.delay);

        result = digitalRead(ports.port_DO);
        delay(ports.delay);

        digitalWrite(ports.port_CLK,LOW);
        delay(ports.delay);

        digitalWrite(ports.port_LED,HIGH);
        delay(DEFAULT_LED_DELAY);
        digitalWrite(ports.port_LED,LOW);
        delay(DEFAULT_LED_DELAY);

        time++;
    }

    digitalWrite(ports.port_CS, LOW);
    delay(ports.delay);

    if(time == MAX_TIME_WAIT){
        return RESULT_WARNING;
    }
    
    return RESULT_SUCCEFUL;
}

int EEP___executeCommand(const ports_93c46wp_t &ports, uint8_t command){
    EEP___portReset(ports);

    digitalWrite(ports.port_CS, HIGH);
    delay(ports.delay);

    int count_words = 1;
    uint8_t data;

    switch(command){
        case COMMAND_EWEN:
            data = COMMAND_EWEN;
            break;
        case COMMAND_EWDS:
            data = COMMAND_EWDS;
            break;
        case COMMAND_ERAL:
            data = COMMAND_ERAL;
            break;
        default:
            return RESULT_WARNING;
            break;
    }

    EEP___printStartCommandBit(ports);
    EEP___printCommand(ports,&data,count_words);

    digitalWrite(ports.port_CS, LOW);
    delay(ports.delay);

    return RESULT_SUCCEFUL;
}

void EEP_modeEWEnable(const ports_93c46wp_t &ports){
    EEP___executeCommand(ports,COMMAND_EWEN);
}
void EEP_modeEWDisable(const ports_93c46wp_t &ports){
   EEP___executeCommand(ports,COMMAND_EWDS);
}
void EEP_eraseAll(const ports_93c46wp_t &ports){
   EEP_modeEWEnable(ports);
   EEP___executeCommand(ports,COMMAND_ERAL);
   EEP___isSuccefulWrite(ports);
}

key_data_t EEP_readKey(const ports_93c46wp_t &ports){

    int count_adress = 3;
    uint8_t query;
    key_data_t result;
    uint8_t **temp_result = new uint8_t *[result.COUNT_BYTE];
    temp_result[0] = new uint8_t [result.COUNT_BYTE];
    temp_result[1] = new uint8_t [result.COUNT_BYTE];
    temp_result[2] = new uint8_t [result.COUNT_BYTE];
    
    for(int i = 0; i < count_adress; i++){
        for(int j = 0; j < result.COUNT_BYTE; j++){
            temp_result[i][j] = 0;
        } 
    }

    uint8_t address[count_adress];
    address[0] = DEFAULT_PREFIX_POSITION;
    address[1] = DEFAULT_KEY_POSITION;
    address[2] = DEFAULT_ACCESS_MODE_POSITION;

    for(int i = 0; i < count_adress; ++i){
        query = COMMAND_READ;
        query = query | address[i];

        EEP___portReset(ports);
        
        digitalWrite(ports.port_CS, HIGH);
        delay(ports.delay);

        EEP___printStartCommandBit(ports);    
        EEP___printCommand(ports,&query,1);

        for(int j = result.COUNT_BYTE-1; j > -1; --j){
            for(int k = 0, last = COMMAND_SIZE-1; k < COMMAND_SIZE; k++){
                digitalWrite(ports.port_CLK, HIGH);
                delay(ports.delay);
            
                temp_result[i][j] |= digitalRead(ports.port_DO);
                if(k != last){
                    temp_result[i][j] = temp_result[i][j] << 1;
                }
                

                digitalWrite(ports.port_CLK, LOW);
                delay(ports.delay);
            }
        }

        digitalWrite(ports.port_CS, LOW);
        delay(ports.delay);
    }

    result.prefix[0] = temp_result[0][0];
    result.prefix[1] = temp_result[0][1];

    result.key[0] = temp_result[1][0];
    result.key[1] = temp_result[1][1];

    result.access_level[0] = temp_result[2][0];
    result.access_level[1] = temp_result[2][1];

    for(int i = 0; i < count_adress; i++){
        delete[] temp_result[i];
    }
    delete[] temp_result;

    return result;
}

bool EEP_writeKey(const ports_93c46wp_t &ports, unsigned int prefix, long int key, unsigned int access_mode){
    
    if(prefix > UINT8_MAX || key > UINT16_MAX || access_mode > (COUNT_ACCESS_LEVEL-1)){
        return false;
    }
    bool write_result = false; 

    int data_bit_one = 0b1111111100000000;
    int data_bit_two = 0b0000000011111111;

    int count_words = 3;
    uint8_t data[count_words];
    EEP_eraseAll(ports);
    EEP___portReset(ports);
    EEP_modeEWEnable(ports);
    EEP___portReset(ports);

    //WRITE Prefix
    digitalWrite(ports.port_CS, HIGH);
    delay(ports.delay);

    data[0] = COMMAND_WRITE;
    data[0] = data[0] | DEFAULT_PREFIX_POSITION;

    data[1] = prefix & data_bit_two;
    data[2] = prefix & data_bit_two;

    EEP___printStartCommandBit(ports);    
    EEP___printCommand(ports,data,count_words);

    digitalWrite(ports.port_CS, LOW);
    delay(ports.delay);

    //нужно постараться дождаться подтверждуния о записи от устройства
    EEP___isSuccefulWrite(ports);

    //WRITE Key
    digitalWrite(ports.port_CS, HIGH);
    delay(ports.delay);
    
    data[0] = 0b01000000;
    data[0] = data[0] | DEFAULT_KEY_POSITION;

    data[1] = key & data_bit_two;
    data[2] = (key & data_bit_one) >> COMMAND_SIZE;

    EEP___printStartCommandBit(ports);    
    EEP___printCommand(ports,data,count_words);

    digitalWrite(ports.port_CS, LOW);
    delay(ports.delay);
        
    EEP___isSuccefulWrite(ports);

    //WRITE Access_mode

    int temp_access_mode;
    switch(access_mode){
        case ACCESS_LEVEL_ENGINEER:
            temp_access_mode = ACCESS_LEVEL_ENGINEER_VALUE;
            break;
        case ACCESS_LEVEL_OPERATOR:
            temp_access_mode = ACCESS_LEVEL_OPERATOR_VALUE;
            break;
        case ACCESS_LEVEL_ADMINISTRATOR:
            temp_access_mode = ACCESS_LEVEL_ADMINISTRATOR_VALUE;
            break;
        case ACCESS_LEVEL_DEVELOPER:
            temp_access_mode = ACCESS_LEVEL_DEVELOPER_VALUE;
            break;
        default:
            temp_access_mode = access_mode;
            break;
    }

    digitalWrite(ports.port_CS, HIGH);
    delay(ports.delay);
    
    data[0] = 0b01000000;
    data[0] = data[0] | DEFAULT_ACCESS_MODE_POSITION;

    data[1] = temp_access_mode & data_bit_two;
    data[2] = temp_access_mode & data_bit_two;

    EEP___printStartCommandBit(ports);    
    EEP___printCommand(ports,data,count_words);

    digitalWrite(ports.port_CS, LOW);
    delay(ports.delay);

    EEP___isSuccefulWrite(ports);

    write_result = EEP_checkWriteKey(ports, prefix, key, access_mode);

    return write_result;
}

bool EEP_checkWriteKey(const ports_93c46wp_t &ports, uint8_t prefix, int key, uint8_t access_mode){
    key_data_t data = EEP_readKey(ports);
    bool result = true;

    uint8_t temp_prefix = (uint8_t)data.prefix[0];
    int temp_key = ((int)data.key[0] << 8) | (int)data.key[1];
    uint8_t temp_acces_key = (uint8_t)data.access_level[0];

    int temp_access_mode;
    switch(temp_acces_key){
        case ACCESS_LEVEL_ENGINEER_VALUE:
            temp_access_mode = ACCESS_LEVEL_ENGINEER;
            break;
        case ACCESS_LEVEL_OPERATOR_VALUE:
            temp_access_mode = ACCESS_LEVEL_OPERATOR;
            break;
        case ACCESS_LEVEL_ADMINISTRATOR_VALUE:
            temp_access_mode = ACCESS_LEVEL_ADMINISTRATOR;
            break;
        case ACCESS_LEVEL_DEVELOPER_VALUE:
            temp_access_mode = ACCESS_LEVEL_DEVELOPER;
            break;
        default:
            temp_access_mode = access_mode;
            break;
    }
    if( temp_prefix == prefix 
        && temp_key == key
        && temp_access_mode == access_mode)
    {
        result = true;
    }
    else{
        result = false;
    }
    
    return result;
}
bool EEP_isWorkKey(const ports_93c46wp_t &ports){
    bool result = true;

    key_data_t data = EEP_readKey(ports);

    uint8_t test_prefix = (uint8_t)rand()%UINT8_MAX;
    int test_key = (int)rand()%UINT16_MAX;
    uint8_t test_acces_mode = (uint8_t)rand()%COUNT_ACCESS_LEVEL;

    if(!EEP_writeKey(ports,test_prefix,test_key,test_acces_mode))
    {
        result = false;
    }

    uint8_t temp_prefix = (uint8_t)data.prefix[0];
    int temp_key = ((int)data.key[0] << 8) | (int)data.key[1];
    uint8_t temp_acces_key = (uint8_t)data.access_level[0];

    switch(temp_acces_key){
        case ACCESS_LEVEL_ENGINEER_VALUE:
            temp_acces_key = ACCESS_LEVEL_ENGINEER;
            break;
        case ACCESS_LEVEL_OPERATOR_VALUE:
            temp_acces_key = ACCESS_LEVEL_OPERATOR;
            break;
        case ACCESS_LEVEL_ADMINISTRATOR_VALUE:
            temp_acces_key = ACCESS_LEVEL_ADMINISTRATOR;
            break;
        case ACCESS_LEVEL_DEVELOPER_VALUE:
            temp_acces_key = ACCESS_LEVEL_DEVELOPER;
            break;
    }

    EEP_writeKey(ports,temp_prefix, temp_key, temp_acces_key);

    return result;
}