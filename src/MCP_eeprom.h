#ifndef MCP_eeprom_h
#define MCP_eeprom_h
#include <Arduino.h>


class MCP_eeprom {
    public:
        MCP_eeprom();

        uint8_t IOnum[64];
        uint8_t AOnum[64];
        
        void write_IOnum(uint8_t io_num[64]);
        void read_IOnum();
        void write_active_outputs(uint8_t io_num[64]);
        void read_active_outputs();
        void write_one_IOnum(int io_num, uint8_t value);
        void write_active_output(int ao_num, uint8_t state);
        void read_active_output(int ao_num);
        void write_clean_IOnum();
        void write_clean_active_outputs();
    
};

#endif //MCP_eeprom_h
