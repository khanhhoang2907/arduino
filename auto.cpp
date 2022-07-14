// #include<WiFi.h>
#include "PubSubClient.h"
// //d 13 trsi t   d12 p t  27 tl 26 pl
// int trig_pin=22;
// int echo_pin=23;
// int distanceCm;
// int distannceR=0;
// int distanceL=0;


// long getDistance(){
//   digitalWrite(trig_pin,LOW);
//   delayMicroseconds(2);
//   digitalWrite(trig_pin,HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trig_pin,LOW);

//   long duration =pulseIn(echo_pin,HIGH);
//   long distanceCm= duration*0.034/2;
//   return distanceCm;

// }


int right_down=12;
int right_reverse=26;
int left_down= 13;
int left_reverse= 27;



void front(){
    digitalWrite(right_down,HIGH);
    digitalWrite(left_down,HIGH);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_reverse,LOW);
}
void right(){
    digitalWrite(right_down,HIGH);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_down,LOW);
    digitalWrite(left_reverse,HIGH);
   
}
void left(){
    digitalWrite(right_reverse,HIGH);
    digitalWrite(left_down,HIGH);
    digitalWrite(left_reverse,LOW);
    digitalWrite(right_down,LOW);
    
}
void behind(){
    digitalWrite(right_reverse,HIGH);
    digitalWrite(left_reverse,HIGH);
    digitalWrite(right_down,LOW);
    digitalWrite(left_down,LOW);
    
}
void stop(){
    digitalWrite(right_down,LOW);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_down,LOW);
    digitalWrite(left_reverse,LOW);
}

void turnLeft(){
    left();
    delay(1000);
    front();
}
void turnRight(){
    right();
    delay(1000);
    front();
}
void move_forward(){
    front();
    delay(5000);
}
void move_backward(){
    behind();
    delay(3000);
}
void setup(){
    Serial.begin(9600);
    pinMode(right_down, OUTPUT);
    pinMode(right_reverse, OUTPUT);
    pinMode(left_down, OUTPUT);
    pinMode(left_reverse, OUTPUT);

}
void loop(){
    

    }