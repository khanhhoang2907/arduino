#include<WiFi.h>
#include "PubSubClient.h"

const char* ssid = "Hoang Anh";
const char* password = "88889999";

const char* mqttServer = "broker.hivemq.com";
const char *MqttId = "12345678";
int port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
const char *TopicSubscribe = "21126072/control";

int distanceCm;
char d[50];

int trig_pin=25;
int echo_pin=33;

int clean =4;

int right_down=12;
int right_reverse=26;
int left_down= 13;
int left_reverse= 27;

//functions

long getDistance();
void wifiConnect();
void mqttReconnect();
void callback(char* topic, byte* message, unsigned int length);
//
void front();
void left();
void right():
void behind();
void stop();
//
void b_front();
void b_left();
void b_right();
void b_behind();
//
//functions

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  wifiConnect();
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

//pinMode
  pinMode(clean, OUTPUT); 


//pinMode
  client.setServer(mqttServer,port);
  client.setCallback(callback);
}

void loop(){
  if(!client.connected())
  {
    mqttReconnect();
  }
  client.loop();
  
    distanceCm= getDistance();
  char buffer[50];
 
  sprintf(d, "%d\n", distanceCm);
   sprintf(buffer," %s ", d );
  client.publish("21126072/out", buffer);
  delay(1000);
  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
 
long getDistance(){
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig_pin, LOW);
  long duration = pulseIn(echo_pin,HIGH);
  long distanceCm = duration*0.034/2;
  return distanceCm;
}

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

void callback(char* topic, byte* message, unsigned int length){
  Serial.println(topic);
  String stMessage;

  for(int i = 0; i < length; i++){
    stMessage += (char)message[i];}
  Serial.println(stMessage);

  if(stMessage =="clean_on"){  // búi hụt on
    digitalWrite(clean,HIGH);
  }
  else if(stMessage =="clean_off"){ // búi hụt off
    digitalWrite(clean,LOW);
  }
  else if(stMessage =="front"){   // front 
        b_front();
    }
  else if(stMessage =="left"){  //left
        b_left();
    }
  else if(stMessage =="right"){  //right
        b_right();
    }
  else if(stMessage =="behind"){  // behind
        b_behind(); 
    }
  else if(stMessage =="auto_on"){   // home

    }
    else if(stMessage =="auto_off"){ //   // end

    }
}

//setting motor 

void b_front(){
    static bool on_front= 0;
    on_front=!on_front;
        if(on_front==true){
            front();
        }
        else{
            stop();
        }   
}
void b_left(){
  static bool on_left= 0;
    on_left=!on_left;
        if(on_left==true){
            left();
        }
        else
            stop();
}
void b_right(){
  static bool on_right= 0;
       on_right=!on_right;
        if(on_right==true){
              right();
        }
        else 
        stop();  
}
void b_behind(){
  static bool on_behind= 0;
    else if(stMessage =="behind"){  // behind
        on_behind=!on_behind;
        if(on_behind==true){
            behind();
    }
        else
        stop();
    }
}

//
void front(){
    digitalWrite(right_down,HIGH);
    digitalWrite(left_down,HIGH);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_reverse,LOW);
    delay(500);
}
void left(){
    digitalWrite(right_down,HIGH);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_down,LOW);
    digitalWrite(left_reverse,HIGH);
    delay(500);
   
}
void right(){
    digitalWrite(right_reverse,HIGH);
    digitalWrite(left_down,HIGH);
    digitalWrite(left_reverse,LOW);
    digitalWrite(right_down,LOW);
    delay (500);
}
void behind(){
    digitalWrite(right_reverse,HIGH);
    digitalWrite(left_reverse,HIGH);
    digitalWrite(right_down,LOW);
    digitalWrite(left_down,LOW);
    delay(500);
}
void stop(){
    digitalWrite(right_down,LOW);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_down,LOW);
    digitalWrite(left_reverse,LOW);
    delay(500);
}