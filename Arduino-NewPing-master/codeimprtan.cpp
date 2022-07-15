

#include<WiFi.h>
#include "PubSubClient.h"

const char* ssid= "Wokwi-GUEST";
const char* password ="";
const char* mqttServer ="test.mosquitto.org";

const char *host ="maker.ifttt.com";
const char*request ="/trigger/Khanh/with/key/cDovp4aBsmNzzYh2rRyAaH4JlBy5ADX_XwRiRK4l38g?value1";
const int port = 80;

WiFiClient espClient;
PubSubClient client(espClient);

void wifiConnect() {
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print("..");
    }
    Serial.println(" Connected!");
}

void sendRequest(int temperature){
  WiFiClient client;
  while(!client.connect(host, port)){      
    Serial.println("connection fail:");
    delay(100);
  }
  client.print(String(" GET ")+request + String(temperature) +" HTTP/1.1\r\n "
                      + " HOST: "+ host + " \r\n " 
                      +" connection: close\r\n\r\n ");
  delay (500);
  while(client.available()){
    String line =client.readStringUntil('\r');
    Serial.print(line);

  }
}

void setup(){
  Serial.begin(9600 );
  Serial.print(" connect to wifi ");

  wifiConnect();
  client.setServer(mqttServer, port);
  sendRequest(45);

  Serial.println(" IP :");
  Serial.println(WiFi.localIP());
}

void mqttReconnect(){
  while(!client.connected()){
    Serial.print("Att MQTT");
    if(client.connect("21126072")){
      Serial.println("connected");
    }
    else{
      Serial.println(" try again in 5 seconds ");
      delay(5000);
    }
  }
}
void loop() {
    if(!client.connected()){
      mqttReconnect();

    }
    client.loop();
    int temp= random(0,100);
    char buffer[50];
    sprintf(buffer, "%d", temp);
    client.publish("21126072/temp",buffer);
    delay(5000);
}
