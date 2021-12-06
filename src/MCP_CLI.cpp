#include "MCP_CLI.h"



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
    if(RS_POSITION > -1) {
        return RS_VALUE.substring(0, RS_POSITION); 
    }
    else {
        return  RS_VALUE;
    }
}

bool MCP_CLI::isCmd(String CMD){
    Serial.println(CMD);
    Serial.println(getCmd() );
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
        return F("else");
}
String MCP_CLI::get1Value() {
    String str = getValue();
    RS_POSITION = str.indexOf(RS_DELIMITER2);
    if(RS_POSITION > -1) 
        return str.substring(0, RS_POSITION); 
    else 
        return F("else");
}

String MCP_CLI::get2Value() {
    String str = MCP_CLI::getValue();

    RS_POSITION = str.indexOf(RS_DELIMITER2);

    if(RS_POSITION > -1) 
        return str.substring(RS_POSITION + 1, RS_VALUE.length());
    else 
        return F("else");
}
void MCP_CLI::serialCom(){
  if(rsReceiver()) {
    if(isCmd(F("set_out"))) {
        int value1 = get1Value().toInt();
        int value2 = get2Value().toInt();
        if(value2 > 0) {
            value2 = 0xff;
        }
        mcp_eeprom_->Write_Output_State(value1, value2);
        mcp_eeprom_->Read_All_Outputs_States();
        Serial.print(value1);
        Serial.print(F(" - set to: "));
        Serial.println(mcp_eeprom_->Active_Outputs[value1], HEX);
    }
    else if(isCmd(F("get_out"))) {
        mcp_eeprom_->Read_All_Outputs_States();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(F(" - "));
            Serial.println(mcp_eeprom_->Active_Outputs[i], HEX);
        }
    }
    else if(isCmd(F("get_io"))) {
        mcp_eeprom_->Read_IO_All_Relations();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(F(" - "));
            Serial.println(mcp_eeprom_->IO_Relations[i]);
        }
    }
    else if(isCmd(F("set_io"))) {
        int value1 = get1Value().toInt();
        int value2 = get2Value().toInt();
        mcp_eeprom_->Write_IO_relation(value1, value2);
        mcp_eeprom_->Read_IO_All_Relations();
        Serial.print(value1);
        Serial.print(F(" - set to: "));
        Serial.println(mcp_eeprom_->IO_Relations[value1]);
    }
    else if(isCmd(F("get_bs"))) {
        mcp_eeprom_->Read_All_BiStable_States();
        for(int i = 0; i < 64; i++){
            Serial.print(i);
            Serial.print(F(": "));
            Serial.println(mcp_eeprom_->BiStable[i]);
        }
    }
    else if(isCmd(F("set_bs"))) {
        int value1 = getValue().toInt();
        int value2 = get2Value().toInt();
        if(value2 > 0)
            value2 = 0xff;
        mcp_eeprom_->Write_BiStable_State(value1, value2);
        mcp_eeprom_->Read_All_BiStable_States();
        Serial.print(value1);
        Serial.print(F(" - set to: "));
        Serial.println(mcp_eeprom_->BiStable[value1]);
    }

  }
}

void MCP_CLI::register_eeprom(MCP_eeprom *mcp_eeprom){
    mcp_eeprom_ = mcp_eeprom;
};

