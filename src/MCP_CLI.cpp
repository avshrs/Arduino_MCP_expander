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
String MCP_CLI::get1Value() {
  String str = MCP_CLI::getValue();
  RS_POSITION = str.indexOf(RS_DELIMITER2);
 if(RS_POSITION > -1) 
      return str.substring(0, RS_POSITION); 
  else 
    return "else";
}

String MCP_CLI::get2Value() {
  String str = MCP_CLI::getValue();

  RS_POSITION = str.indexOf(RS_DELIMITER2);

  if(RS_POSITION > -1) 
      return str.substring(RS_POSITION + 1, RS_VALUE.length());
  else 
    return "else";
}
void MCP_CLI::serialCom(){
  if(rsReceiver()) {

    if(isCmd("set output enable")) {
        int value = getValue().toInt();
        mcp_eeprom_->write_active_output(value, 255);
        mcp_eeprom_->read_active_output(value);
        Serial.print(value);
        Serial.print(" - set to: ");
        Serial.println(mcp_eeprom_->AOnum[value], HEX);
    }
    else if(isCmd("set io")) {
        int value1 = get1Value().toInt();
        int value2 = get2Value().toInt();
        mcp_eeprom_->write_one_IOnum(value1, value2);
        mcp_eeprom_->read_IOnum();
        Serial.print(value1);
        Serial.print(" - set to: ");
        Serial.println(mcp_eeprom_->IOnum[value1], HEX);
    }
    else if(isCmd("set output disable")) {
        int value = getValue().toInt();
        mcp_eeprom_->write_active_output(value, 0);
        mcp_eeprom_->read_active_output(value);
        Serial.print(value);
        Serial.print(" - set to: ");
        Serial.println(mcp_eeprom_->AOnum[value], HEX);
    }
    else if(isCmd("get outputs states")) {
        mcp_eeprom_->read_active_outputs();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(": ");
            Serial.println(mcp_eeprom_->AOnum[i], HEX);
        }
    }
    else if(isCmd("get output state")) {
        int value = getValue().toInt();
        mcp_eeprom_->read_active_outputs();
        Serial.print(value);
        Serial.print(": ");
        Serial.println(mcp_eeprom_->AOnum[value], HEX);
    }
    
    else if(isCmd("help")) {
      Serial.println("set output enable \t\t- set_output_enable,nr");
      Serial.println("set output disable \t\t- set_output_disable,nr");
      Serial.println("get output state \t\t- get_output_state,nr");
      Serial.println("get outputs states \t\t- get_outputs_states");
    }
    else{
        Serial.println("type: help - for more informations");
    }
  }
}

void MCP_CLI::register_eeprom(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
};

