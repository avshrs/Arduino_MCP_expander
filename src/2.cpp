#include <PubSubClient.h>
#include <UIPEthernet.h>
#define DEBUG 1 // Debug output to serial console
#include "DHT.h"
#include <PZEM004T.h>
#define DHTPIN 8  
#define DHTTYPE DHT11 


DHT dht(DHTPIN, DHTTYPE);
PZEM004T pzem(2,3);  // (RX,TX) connect to TX,RX of PZEM
IPAddress i(10,10,1,1);
int sensorPin = A0; // Pin to which the sensor is connected to
unsigned long mytime = 0;
byte mac[] = {0x80, 0x7D, 0x3A, 0x69, 0x20, 0xC8 }; //physical mac address
byte ip[] = {192, 168, 0, 15 }; // ip in lan
const char* mqtt_server = "192.168.0.9";
const char* mqttUser = "user";
const char* mqttPassword = "pass";


char buf[4]; // Buffer to store the sensor value
int updateInterval = 30000; // Interval in milliseconds
EthernetClient espClient;
PubSubClient client(espClient);
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClientSuperior",mqttUser, mqttPassword)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void sensors() {
        int sensorValue = analogRead(sensorPin);
        float h = dht.readHumidity();
        float t = dht.readTemperature();
      
        client.publish("home-assistant/sensor01/brightness", itoa(sensorValue, buf, 10));
        client.publish("home-assistant/sensor02/temperature", String(t).c_str(), true);
        client.publish("home-assistant/sensor02/humidity", String(h).c_str(), true);


        float e = pzem.energy(i);                                          //energia     
        float p = pzem.power(i);                                           //potenza 
        float c = pzem.current(i);                                          //energia     
        float v = pzem.voltage(i);                                           //potenza
                     


        client.publish("home-assistant/sensor03/voltage", String(v).c_str(), true);
        client.publish("home-assistant/sensor03/energy", String(e).c_str(), true);
        client.publish("home-assistant/sensor03/power", String(p).c_str(), true);
        client.publish("home-assistant/sensor03/current", String(c).c_str(), true);
         
          #if DEBUG
            Serial.print("Sensor value: ");
            Serial.println(sensorValue);
            Serial.print("HuM value value: ");
            Serial.println(h);
            Serial.print("Temp value value: ");
            Serial.println(t);
            if(e >= 0.0){ Serial.print(e);Serial.print("Wh; "); }
            if(p >= 0.0){ Serial.print(p);Serial.print("W; "); }
            if(c >= 0.0){ Serial.print(c);Serial.print("A; "); }
            if(v >= 0.0){ Serial.print(v);Serial.print("V; "); }  
            Serial.println();
          #endif   
}
 
void setup()
{
  pzem.setAddress(i);
  Serial.begin(115200);
  delay(100);
  dht.begin();
  Ethernet.begin(mac,ip);
  client.setServer(mqtt_server, 1883);
}
 
void loop()
{
  if (!client.connected()) {    reconnect();  }
  client.loop();
  if (millis()-mytime>updateInterval)
      { mytime=millis(); 
        sensors();
      }
}