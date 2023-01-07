#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <GoogleMaps.h>

const char* ssid = "your_wifi_name";
const char* password = "your_wifi_password";

void setup() {
  // Initialize LoRa radio
  LoRa.begin(433E6);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Initialize Google Maps
  GoogleMaps.begin(map_api_key);
}

void loop() {
  // Check for incoming LoRa packets
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read GPS data from packet
    String data = "";
    while (LoRa.available()) {
      data += (char)LoRa.read();
    }
    
    // Split data into latitude and longitude
    int commaIndex = data.indexOf(',');
    float lat = data.substring(0, commaIndex).toFloat();
    float lon = data.substring(commaIndex+1).toFloat();
    
    // Plot GPS data on map
    GoogleMaps.plot(lat, lon);
  }
}
