#include <Servo.h>
Servo myservo;

bool Auto =0;
bool value_pbot;
bool value_pright;
bool value_pleft;


int pir_bot= 22 ;   
int pir_right= 15 ;
int pir_left= 23;   

int distanceCm;
int distanceRight;
int distanceLeft;

int trig_pin=32;
int echo_pin=35;

int clean =34;

int right_down=12;
int right_reverse=26;
int left_down= 13;
int left_reverse= 27;
char d[20];
char f[20];
int led_behind=14;
int led_left=19;   
int led_right=18;
bool value_fire; // cam bien lua

int fire= 5 ;
long getDistance();

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
int lookLeft();
int lookRight();

void ai();
void warning_fire();///
void thor();///

void setup() {
  Serial.begin(9600);
 
//pinMode
  pinMode(clean, OUTPUT); 
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(right_reverse, OUTPUT);
  pinMode(right_down, OUTPUT);
  pinMode(left_reverse, OUTPUT);
  pinMode(left_down, OUTPUT);
  pinMode(pir_bot,INPUT);
    pinMode(pir_right, INPUT);
    pinMode(pir_left, INPUT);
// LED
  pinMode(led_behind, OUTPUT);
  pinMode(led_right, OUTPUT);
  pinMode(led_left, OUTPUT);
  myservo.attach(33);
  myservo.write(90);
//pinMode
  
}
void loop(){
value_pbot=digitalRead(pir_bot);
  value_pleft=digitalRead(pir_left);
  value_pright=digitalRead(pir_right);
  value_fire=digitalRead(fire);
    distanceCm= getDistance();
    ai(); 
}

void ai(){
    if(pir_bot==1||pir_left==0||pir_right==0||distanceCm <= 40){
        behind();
        delay(30);
        stop();
        delay(300);
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
    else if(pir_bot==0||pir_left==0||pir_right==1||distanceCm > 40){
        front();
        delay(5000);
    }
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
