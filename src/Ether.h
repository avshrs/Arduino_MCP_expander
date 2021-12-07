#ifndef Ether_h
#define Ether_h
#include <Arduino.h>
#include "MCP_eeprom.h"
#include "vars.h"
#include <IPAddress.h>
#include <EtherCard.h>
#include "MCP_eeprom.h"


class Ether_io{
    public:
    
    void Ether_Intit();
    void register_eeprom(MCP_eeprom *mcp_eeprom);
    void check_ether_buffer();
};

#endif //Ether_h
