//https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/



#include <Servo.h>
Servo myservo;

void setup() {
    Serial.begin(9600);
    myservo.attach(25);
}
 

void loop() { 
 for(pos =0; pos<= 180; pos++) {
    myservo.write(pos);
    delay(3);

}
myservo.write(90);
delay(500);K
for(pos =180; pos>= 0; pos--) {
    myservo.write(pos);
    delay(3);

}
}















