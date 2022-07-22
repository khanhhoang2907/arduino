#include <Servo.h>
Servo myservo;

bool Auto =0;


int pir1=23;
int pir2=21;   
bool va_pir1;
bool va_pir2;
int fire=5;
bool va_fire;
int led =25;
int led2=19;
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
int pir_setup();
void ai();


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
  pinMode(led2,OUTPUT);
  pinMode(pir1,INPUT);
  pinMode(pir2,INPUT);
  pinMode(fire,INPUT);
  pinMode(led,OUTPUT);
// LED
  
  myservo.attach(33);
  myservo.write(90);
//pinMode
  
}
void loop(){
    va_pir1=digitalRead(pir1);
    va_pir2=digitalRead(pir2);
    va_fire=digitalRead(fire);
    distanceCm= getDistance();
    
    ai(); 
    delay(1);
}

void ai(){
//   if(va_fire==1){
//         digitalWrite(led,LOW);

//     }
//     else if(va_fire==0){
//         digitalWrite(led,HIGH);}
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
    else if(distanceCm>40||pir_setup()==0){
      digitalWrite(led,LOW);
      digitalWrite(led2,LOW);
        front();
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
    
}