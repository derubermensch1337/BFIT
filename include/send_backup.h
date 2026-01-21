/* Simple backup script to send a string containing all user information to a datacake server. 
 * Yes, this is not very good OPSEC, but the information isnt very sensitive so there shouldnt be any
 * cause for concern.
 */
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <rfid_unlock.h> // The User struct is defined here, might be useful
#include <PubSubClient.h>
#include <WifiClient.h>


WiFiClient = woop;
PubSubClient client(woop);
client.setServer("mqtt.freemqtt.com", 8883);;
client.connect("arduinoClient");
client.publish("test/topic", "Hello from Arduino");

// Configure Authentication Information for Thingsboard
char apitok = EroGpNUbvoa2aFe96dsz;
char url = "http://eu.thingsboard.cloud/api/v1/$ACCESS_TOKEN/telemetry"

// Backup Function Definition
void send_backup(String backup) {
	// Format Request
	String request = String("PUSH ") + url + "--header" + "Host: " + push_bullet_host + "\r\n" + + "Accept: */*\r\n" + "Access-Token: "+ apitok +"\r\n\r\n";

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
