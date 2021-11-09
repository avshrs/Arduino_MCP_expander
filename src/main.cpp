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
    mcp_eeprom.read_IOnum();
    
    mcp_input.init_mcp_devices();
    mcp_output.init_mcp_devices();

    mcp_input.register_ionum(&mcp_eeprom);
    mcp_output.register_ionum(&mcp_eeprom);

    
}

void loop(){
    // scan_inputs.Scan_All_Inputs();
    delay(delay_v);    
}    
