#ifndef MCP_CLI_h
#define MCP_CLI_h
#include <Arduino.h>
#include <stdint.h>
#include "MCP_eeprom.h"
class MCP_CLI{
    public:
    MCP_eeprom *mcp_eeprom_;
    char   RS_CHAR;
    String RS_BUFFER    = "";
    String RS_VALUE     = "";
    char   RS_DELIMITER = ',';
    char   RS_VALUE_DELIMITER = '.';
    int    RS_POSITION  = 0;
    int    RS_POSITION2  = 0;
    char   RS_FLAG      = '\n';

    void register_eeprom(MCP_eeprom *mcp_eeprom);
    void read_command();
    void serialCom();
    bool rsReceiver();
    String getCmd();
    bool isCmd(String CMD);
    String getValue();
    String get2Values();
    

};

#endif //MCP_CLI_h
