#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>




  


const char* ssid="ThienKim";
const char* password = "0918463125";
const char* mqttServer = "broker.hivemq.com";
int port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  wifiConnect();
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttServer, port);
 ----------------------------
}

void wifiConnect()
{
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println("Connected!");
}

void mqttReconnect()
{
  while(!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if(client.connect("12345678"))
    {
      Serial.println("connect");
      client.subscribe("21126072/out");
    }
    else
    {
      Serial.println(" try again in 5 seconds");
      delay(1000);
    }
  }
}

char d[50];
char buffer[50];

void loop() {
    if(!client.connected())
    {
    mqttReconnect();
    }

  client.loop();
int a =9;
  sprintf(d, "%f", a);
  sprintf(buffer,"%s", d);
  client.publish("21126072/outdistance", buffer);
  

}