#ifndef GPIO_CONF_H
#define GPIO_CONF_H
#include <Arduino.h>
#include "vars.h"

class GPIO_CONF {
    public:
        GPIO_CONF();         
        IO_ADDRESS *INPUT_ADDRESS[65];
        IO_ADDRESS *OUTPUT_ADDRESS[65];
        void change_conf();
        
    

};
#endif //GPIO_CONF_H
