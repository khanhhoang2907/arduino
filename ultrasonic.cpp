int echo_pin=33;
int trig_pin=25;

long getdistance(){
    digitalWrite(trig_pin,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin,LOW);

    long duration =pulseIn(echo_pin,HIGH);
    long distanceCM = duration*0.034/2;
    return distanceCM;

}
void setup(){
    Serial.begin(9600);
    pinMode(echo_pin, OUTPUT);
    pinMode(trig_pin, INPUT);
}

void loop(){
     int distance = getdistance();
    Serial.println(distance);

}