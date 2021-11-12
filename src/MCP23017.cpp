#include "MCP23017.h"
#include "vars.h"
#include <Wire.h>
#include <Arduino.h>
#include "print_s.h"
PrintBin print;

MCP::MCP(uint8_t MCPADDRSS, uint8_t GIPOA_TYPE, uint8_t GIPOA_PULL, uint8_t GIPOB_TYPE, uint8_t GIPOB_PULL){
    mcpAddress = MCPADDRSS;

    Wire.begin();
    Wire.beginTransmission(MCPADDRSS);  // expander has I2C address 0x20
    Wire.write(IODIRA);   // register 0 is the I/O direction register for Port A
    Wire.write(GIPOA_TYPE);   //  0x00 for all pins to output mode, 0xFF for all pins to input mode
    Wire.endTransmission();

    if (GIPOA_PULL == 0xFF && GIPOA_TYPE == 0xFF){
        Wire.beginTransmission(MCPADDRSS);  // expander has I2C address 0x20
        Wire.write(GPPUA);   // register 0 is the I/O direction register for Port A
        Wire.write(0xFF);   //  0x00 for all pins to output mode, 0xFF for all pins to input mode
        Wire.endTransmission();
    }


    Wire.beginTransmission (MCPADDRSS);  // expander has I2C address 0x20
    Wire.write(IODIRB);   // register 0 is the I/O direction register for Port A
    Wire.write(GIPOB_TYPE);   //  0x00 for all pins to output mode, 0xFF for all pins to input mode
    Wire.endTransmission();

    if (GIPOB_PULL == 0xFF && GIPOB_TYPE == 0xFF){
        Wire.beginTransmission (MCPADDRSS);  // expander has I2C address 0x20
        Wire.write(GPPUB);   // register 0 is the I/O direction register for Port A
        Wire.write(0xFF);   //  0x00 for all pins to output mode, 0xFF for all pins to input mode
        Wire.endTransmission();
    }
}


uint8_t MCP::readRaw(uint8_t side){
    uint8_t r_value = 0; 
    Wire.beginTransmission(mcpAddress); 
    delay(1);
    Wire.write(side);
    delay(1);
    Wire.endTransmission();
    delay(1);
    Wire.requestFrom((int)mcpAddress, 1);
    while(Wire.available())    
        r_value = convert_bits(Wire.read());
    return ~r_value;
}

uint16_t MCP::readAll(){
    uint8_t addA = GPIOA;
    uint8_t addB = GPIOB;
    uint8_t valueA = readRaw(addA);
    uint8_t valueB = readRaw(addB);
    // print.print_binary8(valueA);
    // print.print_binary8(valueB);
    return uint16_t(valueA) << 8 | uint16_t(valueB);
}    

void MCP::writeRaw(uint8_t side, uint8_t memory){
  Wire.begin();
  Wire.beginTransmission (mcpAddress);
  Wire.write (side);  
  Wire.write (convert_bits(memory));   
  Wire.endTransmission ();
}


uint8_t MCP::convert_bits(uint8_t bits){
    uint8_t tmp = bits;
    int s = sizeof(bits) * 8 - 1;
    for (bits>>= 1; bits; bits>>= 1){   
    tmp <<= 1;
    tmp |= bits& 1;
    s--;
    }
    tmp <<= s;
    return tmp;
}
