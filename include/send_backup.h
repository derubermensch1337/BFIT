/* Simple backup script to send a string containing all user information to a datacake server. 
 * Yes, this is not very good OPSEC, but the information isnt very sensitive so there shouldnt be any
 * cause for concern.
 */
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <rfid_unlock.h> // The User struct is defined here, might be useful
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WifiClient.h>


WiFiClient = woop;
PubSubClient client(woop);
client.setServer("mqtt.freemqtt.com", 8883);;
client.connect("arduinoClient");
client.publish("test/topic", "Hello from Arduino");

// Configure Authentication Information for Thingsboard (without our parameters/header)
char url = "http://eu.thingsboard.cloud/api/v1/EroGpNUbvoa2aFe96dsz/telemetry"

// Backup Function Definition
void send_backup(String* parameters) {
	HTTPClient http;
	char payload[60]
	// Format Request

	if (httpCode > 0) {
		Serial.println("Data sent!");
	} 
	else {
		Serial.println("Error");
	}
	delay(500);
}

void senddata(float reading, int port) {
	setup_wifi();
	client.setCallback(callback);
	
}

void process_string(User* ptr) {
	char backup_string[MAX_ROOMS];
	for (int i = 0; i < MAX_ROOMS; i++) {
		backup_string[i] = *(ptr+i).balance
	}		
}
