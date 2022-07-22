int led=7;
int fire=6;


void setup(){
Serial.begin(9600);
pinMode(led, OUTPUT);;
pinMode(fire, INPUT);
}

void loop(){
 if(digiatalRead(fire)==1){
    digitalWrite(led, HIGH);
 }
 else if(digiatalRead(fire)==0){
    digitalWrite(led, LOW);
 }
}

//git add & git commit -m "khanh" &git push