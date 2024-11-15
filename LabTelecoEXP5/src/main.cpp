
//Libraries

#include <Arduino.h>
#include "DHT.h"
#include "wifi.hpp"
#include "mqtt.hpp"
#include "ota.hpp"
#include "timer.hpp"
#include <ArduinoJson.h>


//Definitions

#define DHTPIN 14
#define DHTTYPE DHT11   // DHT 11

//Init

WiFiClient Inova;
PubSubClient client(Inova);

DHT dht(DHTPIN, DHTTYPE); //Objeto sensor

int pinLedUmbral = 33;
void setup() {

  setup_wifi();
  setup_mqtt();
  setup_ota();

  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  dht.begin();

  pinMode(pinLedUmbral, OUTPUT);
}

void loop() {
  ArduinoOTA.handle();
  loop_mqtt();
 
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  // Manejo PIN ROJO de umbral
  if (t >= 23) {
      digitalWrite(pinLedUmbral, HIGH);
  } else {
      digitalWrite(pinLedUmbral, LOW);
  }

  // JSON 

  // Obtiene la fecha y hora actuales
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Error al obtener la hora");
    return;
  }

  char dateTime[20];
  strftime(dateTime, sizeof(dateTime), "%d/%m/%y - %H:%M", &timeinfo);



}