#include "MCP_CLI.h"
#include <Arduino.h>
#include <stdint.h>




bool MCP_CLI::rsReceiver() {
  if(Serial.available()) {
    RS_CHAR = char(Serial.read());
    if(RS_CHAR == RS_FLAG) {
      RS_VALUE = RS_BUFFER;
      RS_BUFFER = "";
      return true;
    }
    else{
      RS_BUFFER += RS_CHAR;
      return false;
    }
  }
  else 
    return false;
}

String MCP_CLI::getCmd() {
  RS_POSITION = RS_VALUE.indexOf(RS_DELIMITER);
  if(RS_POSITION > -1) 
    return RS_VALUE.substring(0, RS_POSITION); 
  else 
    return  RS_VALUE;
}

bool MCP_CLI::isCmd(String CMD){
  if (getCmd() == CMD)
    return true;
  else 
    return false;
}

String MCP_CLI::getValue() {
  RS_POSITION = RS_VALUE.indexOf(RS_DELIMITER);
  if(RS_POSITION > -1) 
    return RS_VALUE.substring(RS_POSITION + 1, RS_VALUE.length());
  else 
    return "else";
}


void MCP_CLI::serialCom(){
  if(rsReceiver()) {

    if(isCmd("test")) {
      Serial.println("HI im");
    }
    

  

    if(isCmd("help")) {
      Serial.println("delay \t\t- set loop dlelay");
      Serial.println("delay_mu \t\t- set from Miliseconds (1) to Microseconds (0)");
      Serial.println("readMCP1 \t\t- read all values from MCP1 in human");
      Serial.println("BinReadMCP1 \t\t- read all values from MCP1 in binary");
      Serial.println("readMCP2 \t\t- read all values from MCP2 in human");
      Serial.println("BinReadMCP2 \t\t- read all values from MCP2 in binary");
      Serial.println("setMCP\t\t- set output from MCP setMCP e.g. setMCP,1b51 (1) adres of mpc 1, (a) side ,(1) output number , (1) state");
    }
  }
}