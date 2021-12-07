#pragma once
#include <PubSubClient.h>

class MQTT_client{
    void callback(char* topic, byte* payload, unsigned int length);
    void init();
};