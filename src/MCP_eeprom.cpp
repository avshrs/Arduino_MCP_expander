#include "MCP_eeprom.h"
#include <EEPROM.h>

int startFrom = 128;
int IOmin = 0;
int IOmax = 64;

int IOminAddr = startFrom + 0;
int IOmaxAddr = startFrom + 64;

int AOminAddr = startFrom + 64;
int AOmaxAddr = startFrom + 128;

int BSminAddr = startFrom + 128;
int BSmaxAddr = startFrom + 192;

void MCP_eeprom::init_eeprom(){
    MCP_eeprom::Read_IO_All_Relations();
    MCP_eeprom::Read_All_Outputs_States();
}

void MCP_eeprom::Read_IO_All_Relations(){
    for(int i = 0; i < 64; i++){
        IO_Relations[i] = EEPROM.read(i+IOminAddr);
    }
}

void MCP_eeprom::Write_IO_relation(int input_number, uint8_t output_number){
    EEPROM.update(IOminAddr + input_number, output_number);
    IO_Relations[input_number] = output_number;
}

void MCP_eeprom::Read_All_Outputs_States(){
    for(int i = 0; i < 64; i++){
        Active_Outputs[i] = EEPROM.read(i+AOminAddr);
    }
}

void MCP_eeprom::Write_Output_State(int output_number, uint8_t output_state){
    EEPROM.update(AOminAddr+output_number, output_state);
    for(int i = 0; i < 64; i++){
        Active_Outputs[i] = EEPROM.read(i+AOminAddr);
    }
}

void MCP_eeprom::Read_All_BiStable_States(){
    for(int i = 0; i < 64; i++){
        BiStable[i] = EEPROM.read(i+BSminAddr);
    }
}

void MCP_eeprom::Write_BiStable_State(int output_number, uint8_t output_state){
    EEPROM.update(BSminAddr+output_number, output_state);
    for(int i = 0; i < 64; i++){
        BiStable[i] = EEPROM.read(i+BSminAddr);
    }
}
