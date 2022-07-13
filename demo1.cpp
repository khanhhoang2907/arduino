#include<WiFi.h>
#include "PubSubClient.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "test.mosquitto.org";
int port = 1883;


// hut but
int trig_pin=22;
int echo_pin=23;
int distanceCm;
int distannceR=0;
int distanceL=0;



// dong co
int right_down=2;
int right_reverse=12;
int left_down= 5;
int left_reverse= 15;

int led_hut=19;
char d[50]={""};

long getDistance(){
  digitalWrite(trig_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin,LOW);

  long duration =pulseIn(echo_pin,HIGH);
  long distanceCm= duration*0.034/2;
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

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

//
void front(){
    digitalWrite(right_down,HIGH);
    digitalWrite(left_down,HIGH);
}
void left(){
    digitalWrite(right_down,HIGH);
    digitalWrite(right_reverse,HIGH);
   
}
void right(){
    digitalWrite(right_reverse,HIGH);
    digitalWrite(left_down,HIGH);
    
}
void behind(){
    digitalWrite(right_reverse,HIGH);
    digitalWrite(left_reverse,HIGH);
    
}
void stop(){
    digitalWrite(right_down,LOW);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_down,LOW);
    digitalWrite(left_reverse,LOW);
}

void turnLeft(){
    left();
    delay(500);
    front();
}
void turnRight(){
    right();
    delay(500);
    front();
}
void move_forward(){
    front();
    delay(500);
}
void move_backward(){
    behind();
    delay(100);
}

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


// AI
    else if(stMessage =="ai_on"){
        if(distanceCm <=15){
            stop();
            digitalWrite(led_hut,LOW);
            delay(100);
            move_backward();
            delay(300);
            stop():
            delay(200);
            distanceR = lookRight();
            delay(200);
            distanceL = lookLeft();
            delay(200);
            if(distanceR>=distanceL)
                {
                    turnRight();
                    stop();
                }else
                    {
                    turnLeft();
                    stop();
                }
        }
        else
            {
                move_forward();
                digitalWrite(led_hut,HIGH);
            }




        
    }
    else if(stMessage =="ai_off"){

            else if(stMessage =="front"){   // front 
                on_front=!on_front;
                if(on_front==true){
                    front();
                }
                else{
                    stop();
                }
                
            }
            else if(stMessage =="left"){  //left
                on_left=!on_left;
                if(on_left==true){
                    left();
                }
                else
                    stop();
                
            }
            else if(stMessage =="right"){  //right
                on_right=!on_right;
                if(on_right==true){
                    right();
                }
                else 
                stop();
                
            }
            else if(stMessage =="behind"){  // behind
                on_behind=!on_behind;
                if(on_behind==true){
                    behind();
            }
            else
                stop();
            }
            
        }


 
void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi");
  pinMode(12,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(5,OUTPUT);

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

  sprintf(buffer," %s ", d );
  sprintf(d, "%d\n", distanceCm);
  client.publish("21126072/out", buffer);
  
  delay(100);
}
