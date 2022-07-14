#include< Servo.h>
Servo myservo;
void setup() {
    Serial.begin(9600);
    myservo.attach(25);
}

void loop() { 
    myservo.write(90);
}










//https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/
