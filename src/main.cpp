#include <Wire.h>
#include <Arduino.h>
#include "vars.h"
#include "MCP_eeprom.h"
#include "MCP_Output.h"
#include "MCP_input.h"
#include "MCP_CLI.h"

int delay_v = 10;

MCP_eeprom mcp_eeprom;
MCP_Outputs mcp_output;
MCP_Inputs mcp_input;
MCP_CLI mcp_cli;
    

void setup(){
    Serial.begin(1000000);

    Serial.println("Setup Begin");

    mcp_eeprom.init_eeprom();

    mcp_cli.register_eeprom(&mcp_eeprom);
    
    mcp_output.init_mcp_devices();
    delay(1000);

    mcp_output.register_eeprom(&mcp_eeprom);
    
    mcp_input.init_mcp_devices();
    delay(1000);
    mcp_input.add_listener(&mcp_output);
    mcp_input.register_eeprom(&mcp_eeprom);
    
    Serial.println("Setup End");
}

void loop(){
    mcp_input.read_all_inputs();
    mcp_cli.serialCom();
    delay(delay_v);    
}    
