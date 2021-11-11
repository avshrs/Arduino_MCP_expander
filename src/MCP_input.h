#ifndef INPUT_H
#define INPUT_H
#include <Arduino.h>
#include "vars.h"
#include "MCP23017.h"
#include "MCP_Output.h"
#include "MCP_eeprom.h"




class MCP_Inputs {
    private:
    


    MCP *mcpc_in[4];
    public:
        uint16_t inputs_memory[4]={0};
        uint16_t inputs_buffer[4]={0};
        MCP_eeprom *mcp_eeprom_;
        
        void register_ionum(MCP_eeprom *mcp_eeprom);
        void init_mcp_devices();
        void read_all_inputs();
        void add_listener(MCP_Outputs *mcp_outputs, uint8_t input_nr);
        void inform_listener(int input_nr, uint8_t state);


};
#endif //INPUT_H
