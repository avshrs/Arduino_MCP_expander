#ifndef MCP_CLI_h
#define MCP_CLI_h
#include <Arduino.h>
#include "MCP_eeprom.h"
class MCP_CLI{
    public:
    MCP_eeprom *mcp_eeprom_;
    char   RS_CHAR;
    String RS_BUFFER    = "";
    String RS_VALUE     = "";

    int    RS_POSITION  = 0;


    void register_eeprom(MCP_eeprom *mcp_eeprom);
    void read_command();
    void serialCom();
    bool rsReceiver();
    String getCmd();
    bool isCmd(String CMD);
    String getValue();
    String get1Value();
    String get2Value();    
};

#endif //MCP_CLI_h
