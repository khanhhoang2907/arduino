





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

int right_down=12;
int right_reverse=26;
int left_down= 13;
int left_reverse= 27;

int distance;


void front(){
    digitalWrite(right_down,HIGH);
    digitalWrite(left_down,HIGH);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_reverse,LOW);
}
void left(){
    digitalWrite(right_down,HIGH);
    digitalWrite(right_reverse,LOW);
    digitalWrite(left_down,LOW);
    digitalWrite(left_reverse,HIGH);
   
}
void (){
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
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
}
void loop(){
    distance=getdistance();;
    if(distance<50){
        behind();
    }
    else if(distance>=50){
        front();
    }

}