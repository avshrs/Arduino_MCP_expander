#include "Ether.h"
#include "vars.h"
#include <IPAddress.h>
#include <EtherCard.h>
#include "MCP_eeprom.h"


char textToSend[] = "3";
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };
static byte myip[] = { 192,168,1,22 };
static byte mask[] = { 255,255,255,0 };
static byte gwip[] = { 192,168,1,1 };

byte Ethernet::buffer[300]; // tcp/ip send and receive buffer
static uint32_t timer;
const int srcPort PROGMEM = 5656;


MCP_eeprom *mcp_eeprom_;

void checkPayloadData(SERIALMCPFRAME* data){
    if(data->INSTRUCTIONS == 0x00){
        Serial.println(F("Get outputs states"));
        mcp_eeprom_->Read_All_Outputs_States();
        for(int i = 0; i < 64; i++){
            delay(10);
            Serial.print(i);
            Serial.print(" : ");
            Serial.println(mcp_eeprom_->Active_Outputs[i], HEX);
        }
    }
    else if(data->INSTRUCTIONS == 0x01){
        Serial.println(F("Set output state"));
        mcp_eeprom_->Write_Output_State(data->VALUE1, data->VALUE2);
        mcp_eeprom_->Read_All_Outputs_States();
        Serial.print(data->VALUE1);
        Serial.print(" : ");
        Serial.println(mcp_eeprom_->Active_Outputs[data->VALUE1], HEX);
    }

    else if(data->INSTRUCTIONS == 0x03){
        Serial.println(F("Set input output correlation"));
        mcp_eeprom_->Write_IO_relation(data->VALUE1, data->VALUE2);
        mcp_eeprom_->Read_IO_All_Relations();
        Serial.print(data->VALUE1);
        Serial.print(F(" : "));
        Serial.println(mcp_eeprom_->IO_Relations[data->VALUE1]);
    }
    else if(data->INSTRUCTIONS == 0x02){
        Serial.println(F("Get input output correlation"));
        mcp_eeprom_->Read_IO_All_Relations();
        for(int i = 0; i < 64; i++){
            delay(10);
            Serial.print(i);
            Serial.print(" : ");
            Serial.println(mcp_eeprom_->IO_Relations[i]);
        }
    }
    else if(data->INSTRUCTIONS == 0x05){
         Serial.println(F("Set Bistable output conf"));
        if(data->VALUE2 > 0)
            data->VALUE2 = 0xff;
        mcp_eeprom_->Write_BiStable_State(data->VALUE1, data->VALUE2);
        mcp_eeprom_->Read_All_BiStable_States();
        Serial.print(data->VALUE1);
        Serial.print(" : ");
        Serial.println(mcp_eeprom_->BiStable[data->VALUE1]);
    }
    else if(data->INSTRUCTIONS == 0x04){
        Serial.println(F("Get Bistable output conf"));
        mcp_eeprom_->Read_All_BiStable_States();
        for(int i = 0; i < 64; i++){
            delay(10);
            Serial.print(i);
            Serial.print(" : ");
            Serial.println(mcp_eeprom_->BiStable[i]);
        }
    }      
        
        data->INSTRUCTIONS= 0;
        data->VALUE1= 0;
        data->VALUE2= 0;
        data->VALUE3= 0;
    
    }



void udpSerialPrint(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len){
    // IPAddress src(src_ip[0],src_ip[1],src_ip[2],src_ip[3]);

    checkPayloadData((SERIALMCPFRAME*)data);
}


void Ether_io::Ether_Intit(){
 
    if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
        Serial.println(F("Failed to access Ethernet controller"));
    if (!ether.dhcpSetup())
        Serial.println(F("DHCP failed"));

    ether.staticSetup(myip, gwip, NULL, mask);
    ether.udpServerListenOnPort(&udpSerialPrint, 5656);
}

void Ether_io::register_eeprom(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
}

void Ether_io::check_ether_buffer(){
    ether.packetLoop(ether.packetReceive());
    if (millis() > timer) {
      timer = millis() + 5000;
    }
}



