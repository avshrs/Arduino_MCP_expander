#include "MCP_input.h"
#include <Arduino.h>
#include "MCP23017.h"
#include "vars.h"
#include "print_s.h"
#include "MCP_Output.h"

PrintBin print;
MCP *mcpc_in[4];


void MCP_Inputs::init_mcp_devices(){
    mcpc_in[MPC5] = new MCP(MCP5_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in[MPC6] = new MCP(MCP6_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in[MPC7] = new MCP(MCP7_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
    mcpc_in[MPC8] = new MCP(MCP8_ADDR, MCP_IN, MCP_PULLUP, MCP_IN, MCP_PULLUP);
   
}

void MCP_Inputs::register_ionum(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
}

void MCP_Inputs::scan_all_inputs(){
    uint16_t data[4];
    for(int i = MPC5 ; i < 0x08; i++){
        data[i] = mcpc_in[i]-> readAll();
        // Serial.print(i);
        // print->print_binary16(data[i]);
    }
    inputs_memory = uint64_t(data[0]) << 48;
     print.print_binary64(data[0]);
    inputs_memory += uint64_t(data[1]) << 32; 
     print.print_binary64(data[1]);
    inputs_memory +=uint64_t(data[2]) << 16;
     print.print_binary64(data[2]);
    inputs_memory += uint64_t(data[3]);
     print.print_binary64(data[3]);
}


// IO_ADDRESS TranslateNr(int nr){
//     IO_ADDRESS *mcpdata;
//     int side = 0;
//     int address = 32;
//     for(int i = 0 ; i < 64; i++){
//         if(i%8 == 0){
//             side++;
//         }
//         if(i%16 == 0){
//             address ++;
//             side = 0;
//         }
//         if(nr == i+1){
//             print->print_binary64(iputs_memory);
//             mcpdata->MCP_ADDRESS = address;
//             mcpdata->MCP_SIDE = side;
//             mcpdata->MCP_NUMBER = i%8;
//             return *mcpdata;
//         }

// }}