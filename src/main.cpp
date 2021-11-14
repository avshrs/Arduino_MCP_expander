#include <Wire.h>
#include <Arduino.h>
#include "vars.h"
#include "MCP_eeprom.h"
#include "MCP_Output.h"
#include <EtherCard.h>
#include <IPAddress.h>

int delay_v = 0;
// https://github.com/zortness/rocket-mega-shield.git
MCP_eeprom mcp_eeprom;
MCP_Outputs mcp_output;
char textToSend[] = "test 123";


//-begin-------------------------------------------------------------------------//

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700]; // tcp/ip send and receive buffer
static uint32_t timer;
const char website[] PROGMEM = "google.pl";
const int dstPort PROGMEM = 1234;
const int srcPort PROGMEM = 4321;
SERIALMCPFRAME* data_udp;


//callback that prints received packets to the serial port

void checkPayloadData(SERIALMCPFRAME* data){
    
    if(data->INSTRUCTIONS == 0x00){
        //   set output state
        mcp_eeprom.Write_Output_State(data->VALUE1, data->VALUE2);
        mcp_eeprom.Read_All_Outputs_States();
        Serial.print(data->VALUE1);
        Serial.print(":");
        Serial.println(mcp_eeprom.Active_Outputs[data->VALUE1], HEX);
    }
    if(data->INSTRUCTIONS == 0x01){
        //   get outputs states
        mcp_eeprom.Read_All_Outputs_States();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(":");
            Serial.println(mcp_eeprom.Active_Outputs[i], HEX);
        }
    }
    if(data->INSTRUCTIONS == 0x02){
        //   set input output correlation
        mcp_eeprom.Write_IO_relation(data->VALUE1, data->VALUE2);
        mcp_eeprom.Read_IO_All_Relations();
        Serial.print(data->VALUE1);
        Serial.print(":");
        Serial.println(mcp_eeprom.IO_Relations[data->VALUE1]);
    }
    if(data->INSTRUCTIONS == 0x03){
        //   get input output correlations
        mcp_eeprom.Read_IO_All_Relations();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(":");
            Serial.println(mcp_eeprom.IO_Relations[i]);
        }
    }
    if(data->INSTRUCTIONS == 0x04){
        //   set Bistable output conf
        if(data->VALUE2 > 0)
            data->VALUE2 = 0xff;
        mcp_eeprom.Write_BiStable_State(data->VALUE1, data->VALUE2);
        mcp_eeprom.Read_All_BiStable_States();
        Serial.print(data->VALUE1);
        Serial.print(":");
        Serial.println(mcp_eeprom.BiStable[data->VALUE1]);
    }
    if(data->INSTRUCTIONS == 0x05){
        //   get Bistable output conf
        mcp_eeprom.Read_All_BiStable_States();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(":");
            Serial.println(mcp_eeprom.BiStable[i]);
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

//-end---------------------------------

void setup(){
    Serial.begin(1000000);
    
    Serial.println("Setup Begin");

    mcp_eeprom.init_eeprom();

    mcp_output.init_mcp_devices();
    
    mcp_output.register_eeprom(&mcp_eeprom);

       
  //  -----begin---------------------------------------------------------------------//   
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

    //register udpSerialPrint() to port 1337
    ether.udpServerListenOnPort(&udpSerialPrint, 1337);

    //register udpSerialPrint() to port 42.
    ether.udpServerListenOnPort(&udpSerialPrint, 42);
    //-----end-----------------------------------------------------------------------//
    Serial.println("Setup End");

}

void loop(){
    mcp_output.read_all_inputs();
    //--------------------------------------------------------------------------//

    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
      timer = millis() + 5000;
     //static void sendUdp (char *data,uint8_t len,uint16_t sport, uint8_t *dip, uint16_t dport);
     ether.sendUdp(textToSend, sizeof(textToSend), srcPort, ether.hisip, dstPort );
    }
    //--------------------------------------------------------------------------//
    
    delay(delay_v);    
    
}    
