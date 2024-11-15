#ifndef Mqtt_h
#define Mqtt_h

#include <PubSubClient.h>
#include <string>
#include <cstring>
#include "wifi.hpp"


#define MSG_BUFFER_SIZE  (50)

const char* mqtt_server = "YOUR_BROKER";
const char* mqtt_user = "YOUR_USER";
const char* mqtt_password = "YOUR_PASSWORD";

extern WiFiClientSecure LABCONTROL;
extern PubSubClient client;

void reconnect();

void setup_mqtt();

void callback(char* topic, byte* payload, unsigned int length);

void loop_mqtt();

void publish_dht11(float temp, float hum);

#endif