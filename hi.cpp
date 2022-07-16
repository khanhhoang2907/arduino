#include<WiFi.h>
#include "PubSubClient.h"



const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqttServer = "broker.hivemq.com";
const char *MqttId = "12345678";
int port = 1883;
char d[50];
int LED =4;

WiFiClient espClient;
PubSubClient client(espClient);

const char *TopicSubscribe = "21126072/control";

void wifiConnect(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}


void mqttReconnect(){
  while(!client.connected()){
    Serial.print("Attempting MQTT connection...");
    if(client.connect(MqttId)){
      Serial.println("connected");
      client.subscribe(TopicSubscribe);
    }
    else{
      Serial.println("try again in 1 seconds");
      delay(1000);
    }
  }
}

// seting ai



void callback(char* topic, byte* message, unsigned int length){
  Serial.println(topic);
  String stMessage;
 
  for(int i = 0; i < length; i++){
    stMessage += (char)message[i];
  }
  Serial.println(stMessage);
  if(stMessage =="clean_on"){  
    digitalWrite(LED,HIGH);
  }
  else if(stMessage =="clean_off"){  
    digitalWrite(LED,LOW);
  }     
  else if(stMessage =="auto_on"){  
    digitalWrite(LED,HIGH);
  }     
  else if(stMessage =="auto_off"){  
    digitalWrite(LED,LOW);
  }     
}


 
void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
 
  wifiConnect();
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  pinMode(LED, OUTPUT); 

  client.setServer(mqttServer,port);
  client.setCallback(callback);

}

void loop(){
  if(!client.connected())
  {
    mqttReconnect();
  }
  client.loop();
  
 
  // char buffer[50];
 
  // sprintf(d, "%d\n", distanceCm);
  //  sprintf(buffer," %s ", d );
  // client.publish("21126072/out", buffer);
  delay(1000);
  
}


//}test.mosquitto.org


