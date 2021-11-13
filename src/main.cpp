#include <Wire.h>
#include <Arduino.h>
#include "vars.h"
#include "MCP_eeprom.h"
#include "MCP_Output.h"
#include "MCP_input.h"
// #include "MCP_CLI.h"
#include "Ether.h"

int delay_v = 0;

MCP_eeprom mcp_eeprom;
MCP_Outputs mcp_output;
MCP_Inputs mcp_input;
//MCP_CLI mcp_cli;
Ether_io ether_io;    

void setup(){
    Serial.begin(1000000);
    
    Serial.println("Setup Begin");

    mcp_eeprom.init_eeprom();

    ether_io.Ether_Intit();
    ether_io.register_eeprom(&mcp_eeprom);
    
    
    mcp_output.init_mcp_devices();
    
    mcp_output.register_eeprom(&mcp_eeprom);
    ether_io.register_eeprom(&mcp_eeprom);
    mcp_input.init_mcp_devices();
    mcp_input.add_listener(&mcp_output);
    mcp_input.register_eeprom(&mcp_eeprom);
    
    Serial.println("Setup End");
}

void loop(){
    mcp_input.read_all_inputs();
    ether_io.check_ether_buffer();
    // mcp_cli.serialCom();
    delay(delay_v);    
    
}    
