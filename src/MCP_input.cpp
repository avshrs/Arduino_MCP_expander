#include "MCP_input.h"
#include <Arduino.h>
#include "MCP23017.h"
#include "vars.h"
#include "MCP_Output.h"
#include "print_s.h"

PrintBin pb;

void MCP_Inputs::init_mcp_devices(){
    mcpc_in[0] = new MCP(MCP5_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in[1] = new MCP(MCP6_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in[2] = new MCP(MCP7_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in[3] = new MCP(MCP8_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
}

void MCP_Inputs::register_eeprom(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
}

void MCP_Inputs::read_all_inputs(){
    for(int i=0; i<4 ; i++){
        inputs_buffer[i] = mcpc_in[i]->readAll();
    }
    for(int ii=0; ii<4 ; ii++){
        for(int i=0; i<16 ; i++){
            if ((inputs_buffer[ii] & (1 << i )) != (inputs_memory[ii] & (1 << i )) ) {
                if ((inputs_buffer[ii] & (1 << i )) > 0){
                    inform_listener(((ii*16)+i), 0xFF);
                    // pb.print_binary16(inputs_buffer[ii]);
            }
                else if ((inputs_buffer[ii] & (1 << i )) < 1){
                    inform_listener(((ii*16)+i), 0x00);
                    // pb.print_binary16(inputs_buffer[ii]);

                }
            }
        }
    }
    for(int i=0; i<4 ; i++){
        inputs_memory[i] = inputs_buffer[i];
    }
}
void MCP_Inputs::add_listener(MCP_Outputs *mcp_outputs){
    mcp_output_ = mcp_outputs;
}

void MCP_Inputs::inform_listener(int input_nr, uint8_t state){
    mcp_output_->update_output(mcp_eeprom_->IO_Relations[input_nr], state);
}
