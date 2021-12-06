#include "vars.h"
#include "MCP_eeprom.h"
#include "MCP_Manager.h"
// #include "Ether.h"
#include "MCP_CLI.h"
#define delay_v (0)

MCP_eeprom mcp_eeprom;
MCP_Manager mcp_manager;

MCP_CLI mcp_cli;
// Ether_io ether_io;    

void setup(){
    Serial.begin(1000000);
    Serial.println(F("Setup start"));
    mcp_eeprom.init_eeprom();
    Serial.println(F("eeprom iniit"));
    // ether_io.Ether_Intit();
    Serial.println(F("ether init"));
    // ether_io.register_eeprom(&mcp_eeprom);
    
    mcp_manager.init_mcp_devices();
    Serial.println(F("mcp_manager iniit"));
    mcp_manager.register_eeprom(&mcp_eeprom);
    // ether_io.register_eeprom(&mcp_eeprom);
    mcp_manager.init_mcp_devices();
    Serial.println(F("Setup end"));
}

void loop(){
    mcp_manager.read_all_inputs();
    // ether_io.check_ether_buffer();
    mcp_cli.serialCom();
    delay(delay_v);    
    
}    
