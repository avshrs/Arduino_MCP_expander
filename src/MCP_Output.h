#ifndef MCP_Output_h
#define MCP_Output_h
#include <Arduino.h>
#include "Array.h"
#include "vars.h"
#include "MCP_eeprom.h"
#include "MCP23017.h"

class MCP_Outputs {
    public:
    MCP_eeprom *mcp_eeprom_;
    MCP mcpc_out_0;
    MCP mcpc_out_1;
    MCP mcpc_out_2;
    MCP mcpc_out_3;

    MCP *mcpc_out[4];
    
    Array<Array<uint8_t, 2>, 4> outputs_state;
    // uint8_t outputs_state[4][2]={{0,0},{0,0},{0,0},{0,0}}
    void init_mcp_devices();
    void register_eeprom(MCP_eeprom *mcp_eeprom);
    void update_output(int outputm, uint8_t value);
    MCP_Data Get_Data_From_Output(int output_nr);
    void write_output(MCP_Data data, uint8_t value);
};
#endif //MCP_Output_h
