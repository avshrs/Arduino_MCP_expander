#ifndef MCP_eeprom_h
#define MCP_eeprom_h
#include <Arduino.h>


class MCP_eeprom {
    public:
        

        uint8_t IO_Relations[64];
        uint8_t Active_Outputs[64];
        uint8_t BiStable[64];
        void init_eeprom();
        
        void Read_IO_All_Relations();
        void Write_IO_relation(int io_num, uint8_t value);

        void Read_All_Outputs_States();
        void Write_Output_State(int ao_num, uint8_t state);

        void Read_All_BiStable_States();
        void Write_BiStable_State(int out_nr, uint8_t state);
};

#endif //MCP_eeprom_h
