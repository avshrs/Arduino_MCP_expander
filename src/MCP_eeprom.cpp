#include "MCP_eeprom.h"
#include <EEPROM.h>

#define startFrom (128)
#define IOmin (0)
#define IOmax (64)
#define IOminAddr (startFrom + 0)
#define IOmaxAddr (startFrom + 64)
#define AOmin (0)
#define AOmax (64)
#define AOminAddr (startFrom + 64)
#define AOmaxAddr (startFrom + 128)
#define BSmin (0)
#define BSmax (64)
#define BSminAddr (startFrom + 128)
#define BSmaxAddr  (startFrom + 192)


void MCP_eeprom::init_eeprom(){
    MCP_eeprom::Read_IO_All_Relations();
    MCP_eeprom::Read_All_Outputs_States();
}

void MCP_eeprom::Read_IO_All_Relations(){
    for(uint8_t i = IOmin; i < IOmax; i++){
        IO_Relations[i] = EEPROM.read(i+IOminAddr);
    }
}
void MCP_eeprom::Write_IO_relation(int input_number, uint8_t output_number){
    EEPROM.update(IOminAddr + input_number, output_number);
    IO_Relations[input_number] = output_number;
}


void MCP_eeprom::Read_All_Outputs_States(){
    for(uint8_t i = AOmin; i < AOmax; i++){
        Active_Outputs[i] = EEPROM.read(i+AOminAddr);
    }
}

void MCP_eeprom::Write_Output_State(int output_number, uint8_t output_state){
    EEPROM.update(AOminAddr+output_number, output_state);
    for(uint8_t i = AOmin; i < AOmax; i++){
        Active_Outputs[i] = EEPROM.read(i+AOminAddr);
    }
}


void MCP_eeprom::Read_All_BiStable_States(){
    for(uint8_t i = BSmin; i < BSmax; i++){
        BiStable[i] = EEPROM.read(i+BSminAddr);
    }
}

void MCP_eeprom::Write_BiStable_State(int output_number, uint8_t output_state){
    EEPROM.update(BSminAddr+output_number, output_state);
    for(uint8_t i = BSmin; i < BSmax; i++){
        BiStable[i] = EEPROM.read(i+BSminAddr);
    }
}
