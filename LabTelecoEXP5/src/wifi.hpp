#ifndef WIFI_HPP
#define WIFI_HPP

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PSSWD";


int i;

void setup_wifi();

#endif