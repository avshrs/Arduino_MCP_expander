#include "MCP_Output.h"
#include <Wire.h>
#include "vars.h"
#include "MCP23017.h"
#include "MCP_eeprom.h"
#include "print_s.h"


PrintBin pr;
MCP *mcpc_out[4];

void MCP_Outputs::init_mcp_devices(){
    mcpc_out[MPC1] = new MCP(MCP1_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out[MPC2] = new MCP(MCP2_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);
    mcpc_out[MPC3] = new MCP(MCP3_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP);    
    mcpc_out[MPC4] = new MCP(MCP4_ADDR, MCP_OUT, MCP_NOT_PULLUP, MCP_OUT, MCP_NOT_PULLUP); 
    
    
}

void MCP_Outputs::register_ionum(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
}

void MCP_Outputs::print_ionum(){
    for(uint8_t i=0; i<64 ; i++){
        Serial.println(i);
        pr.print_binary8(mcp_eeprom_->IOnum[i]);
    }
}
void MCP_Outputs::register_outputs(){

}
void MCP_Outputs::update_output(){

}
void MCP_Outputs::force_update_value(){

}