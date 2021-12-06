#include "Ether.h"
#include "vars.h"
#include <IPAddress.h>
#include <EtherCard.h>
#include "MCP_eeprom.h"


char textToSend[] = "3";
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };

SERIALMCPFRAME* data_udp;

byte Ethernet::buffer[700]; // tcp/ip send and receive buffer
static uint32_t timer;
const char website[] PROGMEM = "google.pl";
const int dstPort PROGMEM = 1234;
const int srcPort PROGMEM = 5656;

MCP_eeprom *mcp_eeprom_;



void checkPayloadData(SERIALMCPFRAME* data){
    Serial.println(F("check payload"));
    if(data->INSTRUCTIONS == 0x01){
        //   set output state
        mcp_eeprom_->Write_Output_State(data->VALUE1, data->VALUE2);
        mcp_eeprom_->Read_All_Outputs_States();
        Serial.print(data->VALUE1);
        Serial.print(F(" : "));
        Serial.println(mcp_eeprom_->Active_Outputs[data->VALUE1], HEX);
    }
    if(data->INSTRUCTIONS == 0x00){
        //   get outputs states
        mcp_eeprom_->Read_All_Outputs_States();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(F(" : "));
            Serial.println(mcp_eeprom_->Active_Outputs[i], HEX);
        }
    }
    if(data->INSTRUCTIONS == 0x03){
        //   set input output correlation
        mcp_eeprom_->Write_IO_relation(data->VALUE1, data->VALUE2);
        mcp_eeprom_->Read_IO_All_Relations();
        Serial.print(data->VALUE1);
        Serial.print(F(" : "));
        Serial.println(mcp_eeprom_->IO_Relations[data->VALUE1]);
    }
    if(data->INSTRUCTIONS == 0x02){
        //   get input output correlations
        mcp_eeprom_->Read_IO_All_Relations();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(F(" : "));
            Serial.println(mcp_eeprom_->IO_Relations[i]);
        }
    }
    if(data->INSTRUCTIONS == 0x05){
        //   set Bistable output conf
        if(data->VALUE2 > 0)
            data->VALUE2 = 0xff;
        mcp_eeprom_->Write_BiStable_State(data->VALUE1, data->VALUE2);
        mcp_eeprom_->Read_All_BiStable_States();
        Serial.print(data->VALUE1);
        Serial.print(F(" : "));
        Serial.println(mcp_eeprom_->BiStable[data->VALUE1]);
    }
    if(data->INSTRUCTIONS == 0x06){
        //   get Bistable output conf
        mcp_eeprom_->Read_All_BiStable_States();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(F(" : "));
            Serial.println(mcp_eeprom_->BiStable[i]);
        }
    }      
        
        data->INSTRUCTIONS= 0;
        data->VALUE1= 0;
        data->VALUE2= 0;
        data->VALUE3= 0;
    
    }


void udpSerialPrint(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len){
    IPAddress src(src_ip[0],src_ip[1],src_ip[2],src_ip[3]);
    data_udp =(SERIALMCPFRAME*)data;
      checkPayloadData(data_udp);

}


void Ether_io::Ether_Intit(){
 
    if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
        Serial.println(F("Failed to access Ethernet controller"));
    if (!ether.dhcpSetup())
        Serial.println(F("DHCP failed"));

    ether.printIp("IP:  ", ether.myip);
    ether.printIp("GW:  ", ether.gwip);
    
    if (!ether.dnsLookup(website))
        Serial.println("DNS f");

    

    // // register udpSerialPrint() to port 1337
    ether.udpServerListenOnPort(&udpSerialPrint, 5656);

    // // //register udpSerialPrint() to port 42.
    // ether.udpServerListenOnPort(&udpSerialPrint, 42);
}

void Ether_io::register_eeprom(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
}




void Ether_io::check_ether_buffer(){
    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
        timer = millis() + 5000;
     //static void sendUdp (char *data,uint8_t len,uint16_t sport, uint8_t *dip, uint16_t dport);
 
    ether.sendUdp(textToSend, sizeof(textToSend), srcPort, ether.hisip, dstPort );
    }
}



