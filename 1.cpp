
#include<WiFi.h>
int led_behind=24;
int led_front_left=21     ;
int led_front_right=18;

int pir_pin_bot= 22;
int pir_pin_right= 15;
int pir_pin_left= 23;

bool Pirbot;
bool Pirright;
bool Pirleft;
void setup(){
    Serial.begin(115200);
    pinMode(pir_pin_bot,INPUT);
    pinMode(pir_pin_right,INPUT);
    pinMode(pir_pin_left,INPUT);

    pinMode(led_behind,OUTPUT);
    pinMode(led_front_left,OUTPUT);
    pinMode(led_front_right,OUTPUT);

}
void loop(){
    Pirbot= digitalRead(pir_pin_bot);
    Pirright= digitalRead(pir_pin_right);
    Pirleft= digitalRead(pir_pin_left);

    if(Pirbot=1){
        digialWrite(led_behind,HIGH);
        delay(5000);
    }
    else if(Pirright=1){
        digitalWrite(led_front_left,HIGH);
        delay(5000);
    }
    else if(Pirleft=1){
        digitalWrite(led_front_right,HIGH);
        delay(5000);

    }
}