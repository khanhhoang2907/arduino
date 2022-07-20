#define ADCPIN A0
int adcValue;
float voltValue ;
void setup(){
    Serial.begin(115200);

}

void loop(){
    adcValue =analogRead(ADCPIN);
    voltValue =((adcValue*3,3)/4095);
    Serial.println(voltValue);
    delay(100);
    Serial.println(adcValue);
    delay(100);


}