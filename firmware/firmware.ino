#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WiFiManager.h>    

#define Firmware_Date __DATE__
#define Firmware_Time __TIME__

byte ledPin = LED_BUILTIN;

//////////////////////////////////////////////////////////////////////////////////
ESP8266WebServer server(80);        // The Webserver
ESP8266HTTPUpdateServer httpUpdater;

void handleRoot() {
  //This returns the 'homepage' with links to each other main page
  unsigned long days = 0, hours = 0, minutes = 0;
  unsigned long val = millis() / 1000;
  
  days = val / (3600*24);
  val -= days * (3600*24);
  
  hours = val / 3600;
  val -= hours * 3600;
  
  minutes = val / 60;
  val -= minutes*60;

  byte mac[6];
  WiFi.macAddress(mac);

  char szTmp[1024];
  sprintf(szTmp, "<html>"
      "<b>Dashboard for ESP8266 controlled IOT device.</b><br><br>"
    "MAC Address: %02X%02X%02X%02X%02X%02X<br>"
    "Uptime: %02d:%02d:%02d.%02d<br>Free heap: %u<br><br>"
      "<a href='/update'>Update Firmware</a>"
    "</html>",
    mac[0],mac[1],mac[2],mac[3],mac[4],mac[5],
    (int)days, (int)hours, (int)minutes, (int)val, 
    ESP.getFreeHeap());

  server.send(200, "text/html", szTmp);
}

void handleRestart() {
  //This restarts the ESP from a web command in case it is needed
  server.send(200, "text/plain", "ESP is restarting (can also reset with changed URL)");
  server.stop();
  delay(2000);
  ESP.restart();
}

void handleReconfig()
{
  WiFiManager wifiManager;
  // Uncomment and run it once, if you want to erase all the stored information
  wifiManager.resetSettings();
  wifiManager.autoConnect("AutoConnectAP");
  handleRestart();
}

void handleReboot() {
  
  handleRestart();
}

void handleReset() {
  //This resets the ESP from a web command in case it is needed
  server.send(200, "text/plain", "ESP is resetting (can also restart with changed URL)");
  server.stop();
  delay(2000);
  ESP.reset();
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void)
{
  Serial.begin( 115200 );

  // Setup I/O
  pinMode(ledPin, OUTPUT);
  pinMode( D5, INPUT );
  pinMode( D6, INPUT );
  
  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  
  // Uncomment and run it once, if you want to erase all the stored information
  //wifiManager.resetSettings();
  
  wifiManager.autoConnect("AutoConnectAP");

  WiFi.hostname( "Empty");
  
  server.on("/", handleRoot);
  server.on("/restart", handleRestart);
  server.on("/reset", handleReset);
  server.on("/reboot", handleReboot);
  server.on("/reconfig", handleReconfig);
  server.on("/ping", [](){ server.send(200, "text/plain", "{\"ping_alive\": true}"); });

  //Link the HTTP Updater with the web sesrver
  httpUpdater.setup(&server);

  server.onNotFound(handleNotFound);
  server.begin();


}

void loop(void)
{
     
  server.handleClient();

  bool sens1 = digitalRead( D5 );
  bool sens2 = digitalRead( D6 );
  
  if( sens1 && sens2 ) analogWrite(ledPin, 255 );
  if( !sens1 && !sens2 ) analogWrite(ledPin, 0 );
  if( sens1 != sens2 ) analogWrite(ledPin, 230 );

}
