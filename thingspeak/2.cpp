#include <ThingSpeak.h>
#include <WiFi.h>

#define CHANNEL_ID 1805335
#define CHANNEL_API_KEY "OAQLJDH4IFA228CW"

const char* ssid= "Wokwi-GUEST";
const char* password = "";

WiFiClient espClient;

void wifiConnect() {
  WiFi.begin(ssid, password);
  while(WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print("..");
  }
  Serial.println(" Connected!");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print(" connect to wifi ");

  wifiConnect();
  Serial.println(" IP :");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(espClient);
}

void loop() {
  // put your main code here, to run repeatedly:
  ThingSpeak.setField(1,WiFi.RSSI());// 
  ThingSpeak.writeFields(CHANNEL_ID,CHANNEL_API_KEY);
}