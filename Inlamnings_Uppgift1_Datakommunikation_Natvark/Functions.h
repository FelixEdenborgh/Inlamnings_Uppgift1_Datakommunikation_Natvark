#include <ESP8266WiFi.h>


void initSerial(int baud) {
  Serial.begin(baud);
  delay(2000);
  Serial.println("Serial communication initiated.");
}

void initWifi() {
  Serial.println("Wifi communication initiated. Please wait...");
  
  while(WiFi.status() != WL_CONNECTED) { 
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    delay(10000);
  }
  Serial.println(WiFi.localIP());
}

void initWebServer() {
  
  webserver.on("/", login);
  webserver.on("/text", textpage);
  webserver.on("/validatelogin", validateLogin);
  webserver.on("/weather", weatherpage);
  webserver.begin();
  
  Serial.println("Webserver initiated and started.");
}
