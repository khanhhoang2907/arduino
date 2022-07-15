#include<WiFi.h>
#include<string.h>
#include "PubSubClient.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "test.mosquitto.org";
int port = 1883;



static int   distanceCm;
int trig_pin=27;
int echo_pin=26;

int right_down=15;
int right_reverse=25;
int left_down= 13;
int left_reverse= 14;

int led_hut= 2;
char d[50];


long getDistance(){
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig_pin, LOW);
  long duration = pulseIn(echo_pin,HIGH);
  long distanceCm = duration*0.0342/2;
  return distanceCm;
}
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

// seting ai



void callback(char* topic, byte* message, unsigned int length){
  Serial.println(topic);
  String stMessage;
  static bool on_front= 0;
  static bool on_left= 0;
  static bool on_right= 0;
  static bool on_behind= 0;
  for(int i = 0; i < length; i++){
    stMessage += (char)message[i];
  }
  Serial.println(stMessage);
/////////hut 
  if(stMessage =="hut_on"){  // búi hụt on
    digitalWrite(led_hut,HIGH);
  }
  else if(stMessage =="hut_off"){  // búi hụt off
    digitalWrite(led_hut,LOW);
  }


    
}


 
void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  pinMode(right_down,OUTPUT);
  pinMode(right_reverse,OUTPUT);
  pinMode(left_down,OUTPUT);
  pinMode(left_reverse,OUTPUT);

  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  
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
  distanceCm = getDistance();
  Serial.println(distanceCm);
 
  char buffer[50];
 
  sprintf(d, "%d\n", distanceCm);
   sprintf(buffer," %s ", d );
  client.publish("21126072/out", buffer);
  delay(100);
  if(distance<50){
        digitalWrite(34,HIGH);
    }
    else if(distance>=50){
        digitalWrite(34,LOW);
}
}
