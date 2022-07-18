#include<WiFi.h>
#include "PubSubClient.h"
#include <Servo.h>
Servo myservo;

const char* ssid = "Hoang Anh";
const char* password = "88889999";

const char* mqttServer = "broker.hivemq.com";
const char *MqttId = "12345678";
int port = 1883;
bool Auto =0;
WiFiClient espClient;
PubSubClient client(espClient);
const char *TopicSubscribe = "21126072/control";
// khai báo các chân của thiết bị
int distanceCm;
int distanceRight;
int distanceLeft;
char d[50];

int trig_pin=32;
int echo_pin=35;

int clean =34; // đọong cơ máy hút bụi 

int right_down=12;  // khi chân này high thì bánh bên  TRÁI đi TIẾN
int right_reverse=26;  // khi chân này high thì bánh bên TRÁI đi LÙI
int left_down= 13;    // khi chân này high thì bánh bên PHẢI  TIẾN
int left_reverse= 27;   // khi chân này high thì bánh bên PHẢI LÙI
bool Pir;      //  biến này dùng để  nhận giá trị của cảm biến hồng ngoại , 1 là có vật 0 là không có vật 
int pir_pin= 23;  //    chân của ultrasonic
int LED_blue =19;    // cái này giống cái trên

//f
long getDistance();  // hàm đo khoảng csh của ultrasonic
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

void ai();
int lookRight(); 
int lookLeft();
//functions
void callback(char* topic, byte* message, unsigned int length);  // hàm call back nhận giá trị từ node red

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
  pinMode(pir_pin, INPUT);
  pinMode(LED_blue, OUTPUT);
  myservo.attach(33);  // khai báo chân servo 

  myservo.write(90);    // servo đang ở góc 90 độ
//pinMode
  client.setServer(mqttServer,port); // kết nối node red và port trên mạch
  client.setCallback(callback);  // gọi hàm callback
}

void loop(){
  if(!client.connected())
  {
    mqttReconnect();
  }
  client.loop();

  Pir=digitalRead(pir_pin);
  distanceCm= getDistance();
  char buffer[50];
 
  sprintf(d, "%d\n", distanceCm);// chuyển giá trị từ số sang chuỗi ở mảng d
  sprintf(buffer," %s ", d );    // sao chép chuỗi từ mảng d sang buffer
  client.publish("21126072/out", buffer);   // gửi giá trị từ buffer nên node red 


  if(Auto ==1){      // cái này tí xuống hàm callback giải thích rõ hơn 
    ai();
  }
  delay(5);
  
}
/////////
 
long getDistance(){    // đo khoảng cách trả về biến distanceCm
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig_pin, LOW);
  long duration = pulseIn(echo_pin,HIGH);
  long distanceCm = duration*0.034/2;
  return distanceCm;  
}

void wifiConnect(){    // hàm này vớ vẩn không cần quan tâm
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}

void mqttReconnect(){   // hàm này cũng vậy 
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


//
void front(){     // hàm đi tiến 
    digitalWrite(right_down,HIGH);
    digitalWrite(left_down,HIGH);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_reverse,LOW);
    delay(500);
}
void left(){     // này đi sang phải 
    digitalWrite(right_down,HIGH);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_down,LOW);
    digitalWrite(left_reverse,HIGH);
    delay(500);
}
void right(){    // hàm này mới là đi sang phải nè cái cơ nãy là sang trái nhìn tên tiếng anh đi 
    digitalWrite(right_reverse,HIGH);
    digitalWrite(left_down,HIGH);
    digitalWrite(left_reverse,LOW);
    digitalWrite(right_down,LOW);
    delay (500);
}
void behind(){  // tự biết 
    digitalWrite(right_reverse,HIGH);
    digitalWrite(left_reverse,HIGH);
    digitalWrite(right_down,LOW);
    digitalWrite(left_down,LOW);
    delay(500);
}
void stop(){     // chứng minh tương tự 
    digitalWrite(right_down,LOW);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_down,LOW);
    digitalWrite(left_reverse,LOW);
    delay(500);
} 

/////
void b_front(){   //   
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
        else{
            stop();
        }
}
void b_right(){
  static bool on_right= 0;
       on_right=!on_right;
        if(on_right==true){
              right();
        }
        else {
        stop(); 
        } 
}
void b_behind(){
  static bool on_behind= 0;
        on_behind=!on_behind;
        if(on_behind==true){
            behind();
    }
        else{
        stop();
        }
    }
void ai(){
   if(Pir==0 || distanceCm <= 40){  // khi khoảng cách nhở hơn 40 cm hoặc đèn  trên cảm biến hồng ngoại sáng  thì sẽ dừng kại nhìn hai bên, bên nào gần hơn thì chạy qua bên đó
        digitalWrite(LED_blue,HIGH);
        behind();
        delay(30);
        stop();
        lookRight();
        lookLeft();
        delay(100);
        if(distanceRight < distanceLeft){
            right();
            delay(300);
            stop();
            delay(100);
        }
        else if(distanceRight > distanceLeft){
            left();
            delay(300);
            stop();
            delay(100);
        }
    }
    else if(Pir==1 || distanceCm> 40){ // nếu khồn có gì xảy ra chứ chạy thẳng
      digitalWrite(LED_blue,LOW);
        front();
        
    }
}

int lookRight(){     // hàm nhìn bên phải 
    myservo.write(180);              
    delay(1000);
    distanceRight= getDistance();
    myservo.write(90);
    return distanceRight;
}
int lookLeft(){    // nhìn bên trái 
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
  Serial.println(stMessage);   // stMessage là giá trị trả về từ node red ui 

  if(stMessage =="clean_on"){  // búi hụt on
    digitalWrite(clean,HIGH);
  }
  else if(stMessage =="clean_off"){ // búi hụt off
    digitalWrite(clean,LOW);  
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
      
  else if(stMessage =="auto_off"){ //   // end
      Auto =0;
      stop();
  }
  else if(stMessage =="auto_on"){   
      Auto =1;
    }

}