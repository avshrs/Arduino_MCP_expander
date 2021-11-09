#include "MCP_eeprom.h"
#include <EEPROM.h>

int IOminAddr = 0;
int IOmaxAddr = 64;
int AOminAddr = 64;
int AOmaxAddr = 128;

MCP_eeprom::MCP_eeprom(){
    MCP_eeprom::read_IOnum();
    MCP_eeprom::read_active_outputs();
}
// ---------------------------------------------------------
void MCP_eeprom::write_IOnum(uint8_t io_num[64]){
    for(int i = IOminAddr; i < IOmaxAddr; i++){
        EEPROM.write(i, io_num[i]);
        IOnum[i] = io_num[i];
    }
}

void MCP_eeprom::read_IOnum(){
    for(int i = IOminAddr; i < IOmaxAddr; i++){
        IOnum[i] = EEPROM.read(i);
    }
}
void MCP_eeprom::write_one_IOnum(int io_num, uint8_t value){
    EEPROM.write(AOminAddr+io_num, value);
    AOnum[AOminAddr+io_num] = value;
}


// ---------------------------------------------------------
void MCP_eeprom::write_active_outputs(uint8_t ao_num[64]){
    for(int i = AOminAddr; i < AOmaxAddr; i++){
        EEPROM.write(i, ao_num[i]);
        AOnum[i] = ao_num[i];
    }
}
void MCP_eeprom::read_active_outputs(){
    for(int i = AOminAddr; i < AOmaxAddr; i++){
        AOnum[i] = EEPROM.read(i);
    }
}
// ---------------------------------------------------------
void MCP_eeprom::write_active_output(int ao_num, uint8_t state){
    EEPROM.write(AOminAddr+ao_num, state);
    AOnum[AOminAddr+ao_num] = state;
}

void MCP_eeprom::read_active_output(int ao_num){
    AOnum[AOminAddr+ao_num] = EEPROM.read(AOminAddr+ao_num);
}
// ---------------------------------------------------------








void MCP_eeprom::write_clean_IOnum(){
    for(int i = IOminAddr ; i<IOmaxAddr ; i++){
        EEPROM.write(i, i);  
    }
}
void MCP_eeprom::write_clean_active_outputs(){
    for(int i = AOminAddr ; i<AOmaxAddr ; i++){
        EEPROM.write(i, i);  
    }

}
