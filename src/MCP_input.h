#ifndef INPUT_H
#define INPUT_H
#include <Arduino.h>
#include "vars.h"
#include "MCP23017.h"
#include "MCP_Output.h"
#include "MCP_eeprom.h"



class MCP_Inputs {
    public:
        uint64_t inputs_memory=0;
        MCP_eeprom *mcp_eeprom_;
        
        void register_ionum(MCP_eeprom *mcp_eeprom);
        void init_mcp_devices();
        void scan_all_inputs();
        void add_listener(MCP_Outputs *mcp_outputs, uint8_t input_nr);


};
#endif //INPUT_H