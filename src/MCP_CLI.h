#ifndef MCP_CLI_h
#define MCP_CLI_h
#include <Arduino.h>
#include <stdint.h>

class MCP_CLI{
    public:

    char   RS_CHAR;
    String RS_BUFFER    = "";
    String RS_VALUE     = "";
    char   RS_DELIMITER = ',';
    int    RS_POSITION  = 0;
    char   RS_FLAG      = '\n';


    void read_command();
    void serialCom();
    bool rsReceiver();
    String getCmd();
    bool isCmd(String CMD);
    String getValue();

};

#endif //MCP_CLI_h