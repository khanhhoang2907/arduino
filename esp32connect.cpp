#include<WiFi.h>
#include "PubSubClient.h"

const char* ssid = "Hoang Anh";
const char* password = "88889999";
const char* mqttServer = "test.mosquitto.org";
int port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);


void wifiConnect(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}

void mqttReconnect(){
  while(!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if(client.connect("12345678")){
      Serial.println("connected");
      client.subscribe("21126072/control");
      
    }
    else{
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length){
  Serial.println(topic);
  String stMessage;
 
  for(int i = 0; i < length; i++){
    stMessage += (char)message[i];
  }
  Serial.println(stMessage);

}


 
void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  wifiConnect();
  client.setServer(mqttServer,port);

  ///test
  client.setCallback(callback);

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop(){
  if(!client.connected())
  {
    mqttReconnect();
  }
  client.loop();
  
  char buffer[50];

 // sprintf(buffer," %s ", d );
  //sprintf(d, "%d\n", distanceCm);
  client.publish("21126072/out", buffer);
  
  delay(100);
}
