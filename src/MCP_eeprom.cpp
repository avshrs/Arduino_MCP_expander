#include "MCP_eeprom.h"
#include <EEPROM.h>
int startFrom = 128;

void MCP_eeprom::init_eeprom(){
    MCP_eeprom::Read_IO_All_Relations();
    MCP_eeprom::Read_All_Outputs_States();
    MCP_eeprom::Read_All_BiStable_States();
}

void MCP_eeprom::Read_IO_All_Relations(){
    for(int i = 0; i < 64; i++){
        IO_Relations[i] = EEPROM.read(i+startFrom+0);
    }
}
void MCP_eeprom::Write_IO_relation(int input_number, uint8_t output_number){
    EEPROM.update(startFrom+0 + input_number, output_number);
    IO_Relations[input_number] = output_number;
}


void MCP_eeprom::Read_All_Outputs_States(){
    for(int i = 0; i < 64; i++){
        Active_Outputs[i] = EEPROM.read(i+startFrom+64);
    }
}

void MCP_eeprom::Write_Output_State(int output_number, uint8_t output_state){
    EEPROM.update(startFrom+64+output_number, output_state);
    for(int i = 0; i < 0; i++){
        Active_Outputs[i] = EEPROM.read(i+startFrom+64);
    }
}


void MCP_eeprom::Read_All_BiStable_States(){
    for(int i = 0; i < 64; i++){
        BiStable[i] = EEPROM.read(i+startFrom+128);
    }
}

void MCP_eeprom::Write_BiStable_State(int output_number, uint8_t output_state){
    EEPROM.update(startFrom+128+output_number, output_state);
    for(int i = 0; i < 64; i++){
        BiStable[i] = EEPROM.read(i+startFrom+128);
    }
}
