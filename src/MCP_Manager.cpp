#include "MCP_Manager.h"
#include <Wire.h>
#include "vars.h"
#include "MCP23017.h"
#include "MCP_eeprom.h"




void MCP_Manager::init_mcp_devices(){
    mcpc_out_0.MCP_Init(MCP1_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out_1.MCP_Init(MCP2_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out_2.MCP_Init(MCP3_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);    
    mcpc_out_3.MCP_Init(MCP4_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP); 
    mcpc_out[0] = &mcpc_out_0;
    mcpc_out[1] = &mcpc_out_1;
    mcpc_out[2] = &mcpc_out_2;
    mcpc_out[3] = &mcpc_out_3;
    mcpc_in_0.MCP_Init(MCP5_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in_1.MCP_Init(MCP6_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in_2.MCP_Init(MCP7_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in_3.MCP_Init(MCP8_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in[0]= &mcpc_in_0;
    mcpc_in[1]= &mcpc_in_1;
    mcpc_in[2]= &mcpc_in_2;
    mcpc_in[3]= &mcpc_in_3;
    for(int i=0; i<4;i++){
        for(int ii=0; ii<2;ii++){
            outputs_state[i][ii]=0x00;    
        }
    }
}

void MCP_Manager::register_eeprom(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
}

void MCP_Manager::update_output(int output_nr, uint8_t value){
    if(value > 0)
        value = 0xff;
    else 
        value = 0x00;
    MCP_Data data = Get_Data_From_Output(output_nr);        
    uint8_t mask = (1 << data.output);

    if(mcp_eeprom_->Active_Outputs[output_nr]){
        if(mcp_eeprom_->BiStable[output_nr]){
            if(value > 0 ){
                if ((outputs_state[data.chipset][data.side] & mask) > 0){
                    write_output(data, 0x00);
                }
                else{
                    write_output(data, (0xff & mask));
                }
            }
        }
        else{
            Serial.print(F("update_output:"));
            Serial.print(output_nr);
            Serial.print(F(" to "));
            Serial.println(value, HEX);
            write_output(data, value);      
        }
    }
}


void MCP_Manager::read_all_inputs(){
    for(int i=0; i<4 ; i++){
        inputs_buffer[i] = mcpc_in[i]->readAll();
    }
    for(int ii=0; ii<4 ; ii++){
        for(int i=0; i<16 ; i++){
            if ((inputs_buffer[ii] & (1 << i )) != (inputs_memory[ii] & (1 << i )) ) {
                if ((inputs_buffer[ii] & (1 << i )) > 0){
                    update_output(mcp_eeprom_->IO_Relations[((ii*16)+i)], 0xFF);
            }
                else if ((inputs_buffer[ii] & (1 << i )) < 1){
                    update_output(mcp_eeprom_->IO_Relations[((ii*16)+i)], 0x00);
                }
            }
        }
    }
    for(int i=0; i<4 ; i++){
        inputs_memory[i] = inputs_buffer[i];
    }
}

MCP_Data MCP_Manager::Get_Data_From_Output(int output_nr){
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



void MCP_Manager::write_output(MCP_Data data, uint8_t value){
    uint8_t mask = (1 << data.output);
             
    if((outputs_state[data.chipset][data.side] & mask) > (value & mask)){
        outputs_state[data.chipset][data.side] &= ~mask;
    }
    else {
        outputs_state[data.chipset][data.side] |= mask;
    }
    // pb2.print_binary3x8(data.output, data.chipset, outputs_state[data.chipset][data.side]);
    mcpc_out[data.chipset]->writeRaw(data.side, outputs_state[data.chipset][data.side]);
}