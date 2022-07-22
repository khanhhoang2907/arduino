// sang bên code demo.cpp đi bên đấy giống bên này nhưng có giải thích đấy 
#include<WiFi.h>
#include "PubSubClient.h"
#include <Servo.h>
#include <ThingSpeak.h>

#define CHANNEL_ID 1805335
#define CHANNEL_API_KEY "OAQLJDH4IFA228CW"
Servo myservo;

const char* ssid = "Hoang Anh";
const char* password = "88889999";

const char* mqttServer = "broker.hivemq.com";
const char *MqttId = "12345678";
int port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
const char *TopicSubscribe = "21126072/control";

int distanceCm;
int distanceRight;
int distanceLeft;
char d[50];
char f[50];

int trig_pin=32;
int echo_pin=35;

int clean =34;

int right_down=12;
int right_reverse=26;
int left_down= 13;
int left_reverse= 27;

int led =25;
int led2=19;

int pir1=23;   bool va_pir1;
int pir2=21;   bool va_pir2;
int fire=5;    bool va_fire;


bool Auto =0;
//functions

long getDistance();
void wifiConnect();
void mqttReconnect();

void front();
void left();
void right();
void behind();
void stop();

//
void b_front();
void b_left();
void b_right();
void b_behind();
//
int pir_setup();
void ai();
int lookRight();
int lookLeft();
//functions
void callback(char* topic, byte* message, unsigned int length);
//
void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  wifiConnect();
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

//pinMode
  pinMode(clean, OUTPUT); 
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(right_reverse, OUTPUT);
  pinMode(right_down, OUTPUT);
  pinMode(left_reverse, OUTPUT);
  pinMode(left_down, OUTPUT);
  pinMode(pir1,INPUT);
  pinMode(pir2,INPUT);
  pinMode(fire,INPUT);
  pinMode(led2,OUTPUT);
  pinMode(led,OUTPUT);

  myservo.attach(33);
  myservo.write(90);
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

  va_pir1=digitalRead(pir1);
  va_pir2=digitalRead(pir2);
  va_fire=0//digitalRead(fire);
  

  char buffer[50];
  char buffer2[50];
  sprintf(f, "%d", va_fire);
  sprintf(buffer2," %s ", f );
  client.publish("21126072/outfire", buffer2);
  distanceCm= getDistance();

  sprintf(d, "%d", distanceCm);
  sprintf(buffer2," %s ", d );
  client.publish("21126072/outdistance", buffer2);
  if(Auto ==1){
    ai();
  }
  //  ThingSpeak.setField(1,WiFi.RSSI());// 
  // ThingSpeak.writeFields(CHANNEL_ID,CHANNEL_API_KEY);
  delay(5);
  
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
      Serial.println("try again in 3 seconds");
      delay(1000);
    }
  }
}

int pir_setup(){
  if(va_pir1==1){
    return 1;
  }
  else if(va_pir1 ==0){
    if(va_pir2==0)
    {
      return 1;
    }
    else if(va_pir2==1)
     {
       return 0;
     }
  }
}
void ai(){
   if(distanceCm <= 40|| pir_setup()==1){
      digitalWrite(led,HIGH);
        stop();
        lookRight();
        lookLeft();
        delay(1000);
        behind();
        
        stop();
        
        if(distanceRight < distanceLeft){
            right();
            delay(600);
            stop();
            delay(100);
        }
        else if(distanceRight > distanceLeft){
            left();
            delay(600);
            stop();
            delay(100);
        }
    }
    else if(distanceCm>40||pir_setup()==0){
      digitalWrite(led,LOW);
      digitalWrite(led2,LOW);
        front();
    }
    
}
//setting motor 

void b_front(){
    static bool on_front= 0;
    on_front=!on_front;
        if(on_front==true){front();}
        else{stop();}   
}
void b_left(){
  static bool on_left= 0;
    on_left=!on_left;
        if(on_left==true){left();}
        else{stop();}
}
void b_right(){
  static bool on_right= 0;
       on_right=!on_right;
        if(on_right==true){right();}
        else {stop(); } 
}
void b_behind(){
  static bool on_behind= 0;
        on_behind=!on_behind;
        if(on_behind==true){behind();}
        else{stop();}
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
   digitalWrite(led2,HIGH);
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


int lookRight(){
    myservo.write(180);              
    delay(1000);
    distanceRight= getDistance();
    myservo.write(90);
    return distanceRight;
}
int lookLeft(){
    myservo.write(0);             
    delay(1000);
    distanceLeft= getDistance();
    myservo.write(90);
    return distanceLeft;
}
void callback(char* topic, byte* message, unsigned int length){
  Serial.println(topic);
  String stMessage;

  for(int i = 0; i < length; i++){
    stMessage += (char)message[i];}
  Serial.println(stMessage);

  if(stMessage =="clean_on"){  
    digitalWrite(clean,HIGH);
  }
  else if(stMessage =="clean_off"){ 
    digitalWrite(clean,LOW);  }

  else if(stMessage =="led_off"){  
          digitalWrite(led,LOW); 
        }
  else if(stMessage =="led_on"){ 
    digitalWrite(led,HIGH);  
        }
  else if(stMessage =="front"){  
            b_front(); 
        }
  else if(stMessage =="left"){  
            b_left(); 
  }
  else if(stMessage =="right"){  
            b_right(); 
        }
  else if(stMessage =="behind"){  
            b_behind(); 
        }
  else if(stMessage =="auto_off"){ 
      Auto =0;
      stop();
  }
  else if(stMessage =="auto_on"){   
      Auto =1;
    }

}