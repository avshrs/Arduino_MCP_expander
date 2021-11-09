#include "GPIO_conf.h"
#include "vars.h"
#include <Wire.h>
#include <Arduino.h>

GPIO_CONF::GPIO_CONF(){
    uint8_t address_ = 0x20;
    uint8_t side = 0x00;
        
    for(int a = 0; a < 64; a++){
        if(a%8 == 0 ){
            side++;
        }
        if(a%16 == 0 ){
            address_++;
            side = 0x00;
        }
        
        INPUT_ADDRESS[a+1]->MCP_ADDRESS = address_;
        INPUT_ADDRESS[a+1]->MCP_SIDE = side;
        INPUT_ADDRESS[a+1]->MCP_NUMBER = (a%8);    
    }
      
}


void GPIO_CONF::change_conf(){


}