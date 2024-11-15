
#include "mqtt.hpp"
#include "wiFi.hpp"


void reconnect() {
    int i=0;
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "Esp32_LabControl";
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.publish("Status", "Connected");
      client.subscribe("lab/sensor");   //Control Topic
    } else {
      i++;
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 2 seconds");
      delay(2000);
    }
    if(i>15){
      i=0;
      ESP.restart();
      }
  }
}

void setup_mqtt() {
  LABCONTROL.setInsecure();
  client.setServer(mqtt_server, 8883);
  client.setCallback(callback);
}

void loop_mqtt() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED off by making the voltage HIGH
  }
}

void publish_dht11(float temp, float hum) {
//Create a JSON oject to publish the data
 char message[100];
 sprintf(message, "{\"sender\":\"GRUPO_2\" \"temp\": %.2f, \"hum\": %.2f, \"date\": %.2f}", temp, hum, 69.0);
    client.publish("lab/sensor", message);
}
