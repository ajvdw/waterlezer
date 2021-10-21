#include <WiFiManager.h>    

#define Firmware_Date __DATE__
#define Firmware_Time __TIME__

byte ledPin = LED_BUILTIN;

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
  wifiManager.resetSettings();
  
  wifiManager.autoConnect("WaterLezer");

  WiFi.hostname( "WaterLezer");
}

void loop(void)
{
  bool sens1 = digitalRead( D5 );
  bool sens2 = digitalRead( D6 );
  
  if( sens1 && sens2 ) analogWrite(ledPin, 255 );
  if( !sens1 && !sens2 ) analogWrite(ledPin, 0 );
  if( sens1 != sens2 ) analogWrite(ledPin, 230 );

}
