#include "OTA.hpp"


void updateOTA(char url[]){
	WiFiClient client;
	Serial.println("OTA Updating SPIFFS...");

	t_httpUpdate_return ret = httpUpdate.updateSpiffs(client, url);
	if (ret == HTTP_UPDATE_OK) {
		Serial.println("OTA Updating sketch...");
		ret = httpUpdate.update(client, url);

		switch (ret) {
			case HTTP_UPDATE_FAILED:
				Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
			break;

			case HTTP_UPDATE_NO_UPDATES:
				Serial.println("HTTP_UPDATE_NO_UPDATES");
			break;

			case HTTP_UPDATE_OK:
				Serial.println("HTTP_UPDATE_OK");
			break;
		}
	}
}

