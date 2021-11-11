#include "MCP_eeprom.h"
#include <EEPROM.h>
int startFrom = 128;
int IOmin = 0;
int IOmax = 64;
int IOminAddr = startFrom + 0;
int IOmaxAddr = startFrom + 64;
int AOmin = 0;
int AOmax = 64;
int AOminAddr = startFrom + 64;
int AOmaxAddr = startFrom + 128;

void MCP_eeprom::init_eeprom(){
    MCP_eeprom::read_IOnum();
    MCP_eeprom::read_active_outputs();
}
// ---------------------------------------------------------
void MCP_eeprom::write_IOnum(uint8_t io_num[64]){
    for(int i = IOmin; i < IOmax; i++){
        EEPROM.update(i+IOminAddr, io_num[i]);
        IOnum[i] = io_num[i];
    }
}

void MCP_eeprom::read_IOnum(){
    for(int i = IOmin; i < IOmax; i++){
        IOnum[i] = EEPROM.read(i+IOminAddr);
    }
}
void MCP_eeprom::write_one_IOnum(int io_num, uint8_t value){
    EEPROM.update(AOminAddr+io_num, value);
    AOnum[io_num] = value;
}
// ---------------------------------------------------------

void MCP_eeprom::read_active_outputs(){
    for(int i = AOmin; i < AOmax; i++){
        AOnum[i] = EEPROM.read(i+AOminAddr);
    }
}

void MCP_eeprom::write_active_output(int ao_num, uint8_t state){
    EEPROM.update(AOminAddr+ao_num, state);
    for(int i = AOmin; i < AOmax; i++){
        AOnum[i] = EEPROM.read(i+AOminAddr);
    }
}

void MCP_eeprom::read_active_output(int ao_num){
    AOnum[ao_num] = EEPROM.read(AOminAddr+ao_num);
}
// ---------------------------------------------------------








void MCP_eeprom::write_clean_IOnum(){
    for(int i = IOminAddr ; i<IOmaxAddr ; i++){
        EEPROM.update(i, i);  
    }
}
void MCP_eeprom::write_clean_active_outputs(){
    for(int i = AOminAddr ; i<AOmaxAddr ; i++){
        EEPROM.update(i, i);  
    }

}
