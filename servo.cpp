//https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/



#include <Servo.h>
Servo myservo;

void setup() {
    Serial.begin(9600);
    myservo.attach(25);
}
int lookRight()
{
    myservo.write(50); 
    delay(500);
   // int distance = readPing();
    delay(100);
    myservo.write(115); 
   // return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    //int distance = readPing();
    delay(100);
    myservo.write(115); 
   // return distance;
    delay(100);
}

// int readPing() { 
//   delay(70);
//   int cm = sonar.ping_cm();
//   if(cm==0)
//   {
//     cm = 250;
//   }
//   return cm;
// }
void loop() { 
   

}




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


























