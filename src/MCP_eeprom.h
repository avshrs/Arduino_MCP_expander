#ifndef MCP_eeprom_h
#define MCP_eeprom_h
#include <Arduino.h>


class MCP_eeprom {
    public:
        

        uint8_t Output_relations[64];
        // 1111 0000  input number connected to output
        // 0000 1111  

        uint8_t InputConf[64];
        // bit 1 << 0 - input 1 - switch 
        // bit 1 << 1 - input 1 - Activated Alarm 
        // bit 1 << 2 - input 1 - Armed Alarm
        // bit 1 << 3 - input 1 - twilight sensor
        // bit 1 << 4 - input 1 - 
        // bit 1 << 5 - input 1 - 
        // bit 1 << 6 - input 1 - 
        // bit 1 << 7 - input 1 - 

        uint8_t OutputConf[64];
        // bit 1 << 0 - output 1 - ON | 0 -OFF
        // bit 1 << 1 - output 1 - Bistable | 0 - Monostable
        // bit 1 << 2 - output 1 - OFF by Armed Alarm |  0 none
        // bit 1 << 3 - output 1 - ON by Activated Alarm | 0 None
        // bit 1 << 4 - output 1 - ON by Activated PIR Sensor
        // bit 1 << 5 - output 1 - ON by twilight sensor | 0 None
        // bit 1 << 6 - output 1 - 
        // bit 1 << 7 - output 1 - 
        

        void init_eeprom();
        uint8_t Get_IO_relation(uint8_t input_number);
        void Set_IO_relation(uint8_t input_number, uint8_t output_number);

        uint8_t Get_Alarm_input(uint8_t input_number);
        void Set_IO_relation(uint8_t input_number, uint8_t output_number);


        uint8_t Get_Output_state(uint8_t output_number);
        void Set_Output_state(uint8_t output_number, uint8_t state);

        void Read_All_Outputs_States();
        void Write_Output_State(int ao_num, uint8_t state);

        void Read_All_BiStable_States();
        void Write_BiStable_State(int out_nr, uint8_t state);
};

#endif //MCP_eeprom_h
