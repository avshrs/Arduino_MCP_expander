#ifndef Ether_h
#define Ether_h
#include <Arduino.h>
#include "MCP_eeprom.h"
#include "vars.h"
#include <IPAddress.h>
#include <EtherCard.h>
#include "MCP_eeprom.h"


class Ether{
    public:
    MCP_eeprom *mcp_eeprom_;
    SERIALMCPFRAME* data_udp;
    void checkPayloadData(SERIALMCPFRAME* data);
    void udpSerialPrint(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len);
    void Ether_Intit();
    void register_eeprom(MCP_eeprom *mcp_eeprom);
};

#endif //Ether_h
