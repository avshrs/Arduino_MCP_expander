#ifndef MCP_Output_h
#define MCP_Output_h
#include <Arduino.h>
#include "vars.h"
#include "MCP_eeprom.h"
#include "MCP23017.h"

class MCP_Outputs {
    private:
    MCP_eeprom *mcp_eeprom_;
    MCP *mcpc_out[4];
    
    
    public:
    struct MCP_Data
    {
        uint8_t chipset;
        uint8_t side;
        uint8_t value;
    };  
    uint8_t outputs_state[4][2]={0};
    
    void init_mcp_devices();
    void register_eeprom(MCP_eeprom *mcp_eeprom);
    void update_output(int outputm, uint8_t value);
    MCP_Data Get_Data_From_Output(int output_nr, uint8_t value);
};
#endif //MCP_Output_h
