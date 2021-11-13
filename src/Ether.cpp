#include "Ether.h"
#include "vars.h"
#include <IPAddress.h>
#include <EtherCard.h>


char textToSend[] = "test 123";
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700]; // tcp/ip send and receive buffer
static uint32_t timer;
const char website[] PROGMEM = "google.pl";
const int dstPort PROGMEM = 1234;
const int srcPort PROGMEM = 4321;


void Ether::Ether_Intit(){
 
    if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
        Serial.println(F("Failed to access Ethernet controller"));
    if (!ether.dhcpSetup())
        Serial.println(F("DHCP failed"));

    ether.printIp("IP:  ", ether.myip);
    ether.printIp("GW:  ", ether.gwip);
    ether.printIp("DNS: ", ether.dnsip);
    
    if (!ether.dnsLookup(website))
        Serial.println("DNS failed");

    ether.printIp("SRV: ", ether.hisip);

    // //register udpSerialPrint() to port 1337
    // ether.udpServerListenOnPort(&udpSerialPrint, 1337);

    // //register udpSerialPrint() to port 42.
    // ether.udpServerListenOnPort(&udpSerialPrint, 42);
}

void Ether::register_eeprom(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
}
void Ether::checkPayloadData(SERIALMCPFRAME* data){
    // Print walue on one sensor 
    if(data->INSTRUCTIONS == 0x00){  
        // mcpc[data->MCPNR]->writeOne((uint8_t)((data->VALUE)>>4),(uint8_t)(data->VALUE)&0x0F, (uint8_t)data->MCPSIDE, FORCE);
    }
    // Print to all at once 
    else if(data->INSTRUCTIONS == 0x01){  
        // mcpc[data->MCPNR]->writeAll(data->VALUE, data->MCPSIDE, FORCE);
    }
    // Print values from side 
    else if(data->INSTRUCTIONS == 0x11){  
        // mcpc[data->MCPNR]->readAll(data->MCPSIDE);
        //print on serial 
        /*
        TO DO
        communication back to leasener on ip;
        */
    }    
    
    
        data->MCPNR= 0;
        data->MCPSIDE = 0;
        data->INSTRUCTIONS= 0;
        data->VALUE= 0;
    }



void Ether::udpSerialPrint(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len){
    IPAddress src(src_ip[0],src_ip[1],src_ip[2],src_ip[3]);
    data_udp =(SERIALMCPFRAME*)data;
      checkPayloadData(data_udp);
}



void check_ether_buffer(){
        ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
      timer = millis() + 5000;
     //static void sendUdp (char *data,uint8_t len,uint16_t sport, uint8_t *dip, uint16_t dport);
 
     ether.sendUdp(textToSend, sizeof(textToSend), srcPort, ether.hisip, dstPort );
    }
}