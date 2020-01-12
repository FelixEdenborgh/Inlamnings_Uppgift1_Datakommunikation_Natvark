/*
 *  Glöm inte andra WIFI_SSID och WIFI_PASS i config.h 
 *  Gå in och ändra e-postkontot och lösenordet i config.h
 *  eller använd e-postadressen mupp@test.se och lösenordet password
 */

#include <ESP8266WebServer.h>
ESP8266WebServer webserver(80);

#include "Config.h"             // innehåller inställningar som ssid etc.
#include "Websites.h"           // innehåller alla hemsidor som används
#include "Functions.h"          // innehåller alla init-funktioner


void setup() {
  test();
  initSerial(115200);           
  initWifi();                   
  initWebServer(); 
    

             
}

void loop() {
  receiver();
  webserver.handleClient();
}
