#ifndef INPUT_H
#define INPUT_H
#include <Arduino.h>
#include "vars.h"
#include "MCP23017.h"
#include "MCP_Output.h"
#include "MCP_eeprom.h"

class MCP_Inputs {
    private:
        MCP_Outputs *mcp_output_;
        MCP mcpc_in_0;
        MCP mcpc_in_1;
        MCP mcpc_in_2;
        MCP mcpc_in_3;
        MCP *mcpc_in[4];
        MCP_eeprom *mcp_eeprom_;
    public:
        uint16_t inputs_memory[4]={0};
        uint16_t inputs_buffer[4]={0};
        
        void register_eeprom(MCP_eeprom *mcp_eeprom);
        void init_mcp_devices();
        void read_all_inputs();
        void add_listener(MCP_Outputs *mcp_outputs);
        void inform_listener(int input_nr, uint8_t state);

};
#endif //INPUT_H
