#ifndef MCP_Output_h
#define MCP_Output_h
#include <Arduino.h>
#include "MCP_eeprom.h"

class MCP_Outputs {
    public:
    MCP_eeprom *mcp_eeprom_;

    uint8_t mcpAddress = 0x20;
    uint64_t outputs_state = 0;
    uint64_t forced_flag = 0;
    uint64_t foced_value = 0; 
    char output_name[64][10];
    uint8_t ioselector[64];

    void init_mcp_devices();
    void register_ionum(MCP_eeprom *mcp_eeprom);
    void print_ionum();
    
    void register_outputs();
    void update_output();
    void force_update_value();


};
#endif //MCP_Output_h
