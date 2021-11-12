#include "MCP_Output.h"
#include <Wire.h>
#include "vars.h"
#include "MCP23017.h"
#include "MCP_eeprom.h"
#include "print_s.h"
PrintBin pb2;


void MCP_Outputs::init_mcp_devices(){
    mcpc_out[0] = new MCP(MCP1_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out[1] = new MCP(MCP2_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out[2] = new MCP(MCP3_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);    
    mcpc_out[3] = new MCP(MCP4_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP); 
    for(int i = 0; i<4; i++){
        mcpc_out[i]->writeRaw(GPIOA, 0x00);
        mcpc_out[i]->writeRaw(GPIOB, 0x00);
    }
    
}

void MCP_Outputs::register_eeprom(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
}

void MCP_Outputs::update_output(int output_nr, uint8_t value){
    if(value > 0 ){
        value = 0xff;
    }
    else 
        value = 0x00;
    for(int i = 0;i<4;i++){
        for(int ii =0 ; ii<2;ii++){
            outputs_state[i][ii]=0x00;
        }
    }        
    if(mcp_eeprom_->Active_Outputs[output_nr]){
        if(mcp_eeprom_->BiStable[output_nr]){
        
        }
        
        else{
            MCP_Data data = Get_Data_From_Output(output_nr);
        uint8_t st = outputs_state[data.chipset][data.side];
            uint8_t mask = (1 << data.output);
                Serial.print(data.chipset);
                Serial.print(" ");
                Serial.print(data.side, HEX);
                Serial.print(" ");
                Serial.print(data.output);
                Serial.print(" ");
            
            if((outputs_state[data.chipset][data.side] & mask) > (value & mask)){
                outputs_state[data.chipset][data.side] &= ~mask;
            }
            else {
                outputs_state[data.chipset][data.side] |= mask;
            }
            pb2.print_binary3x8(st,outputs_state[data.chipset][data.side],  outputs_state[data.chipset][data.side]);
            mcpc_out[data.chipset]->writeRaw(data.side, outputs_state[data.chipset][data.side]);
        }
    }
}

MCP_Data MCP_Outputs::Get_Data_From_Output(int output_nr){
    MCP_Data data; 
    int chipset = (output_nr-(output_nr%16))/16;
    int chipset_outs = output_nr - (chipset*16);
    int chipset_out = 0;
    uint8_t side = 0;
    if(chipset_outs > 7){
        side = GPIOA; 
        chipset_out = chipset_outs-8;
    }
    else {
        side = GPIOB; 
        chipset_out = chipset_outs;
    }
    
    data.chipset = chipset;
    data.side = side;
    
    data.output = chipset_out;
    return data;
}