#include <WiFi.h>
#include <ArduinoJson.h>
 
const char* ssid     = "Wokwi-GUEST";  
const char* password = "";
 
const char* host     = "Arduinoduster.000webhostapp.com"; // Your domain  
String path          = "/email-notification.php?api_key_esp=tPmAT5Ab3j7F9"; // Cái này tự đặt
String path_value    = "&PIN12=0";  
 
 
void setup() {  
 
  
//  pinMode(14, OUTPUT); 
//  pinMode(13, OUTPUT); 
//  pinMode(12, OUTPUT); 
  pinMode(12, INPUT_PULLUP);
  Serial.begin(115200);
 
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("WiFi connected");  
 // Serial.println("IP address: " + WiFi.localIP());
}
 
void loop() {  
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
count=0;
while(1)
{
      
        if(count==lost)
          {
            Serial.println("OOPS-Connetion FAIL");
            Serial.println("Retry connect HOST");    
            err++; 
                                      
            break;
                            
          }
 // Nếu lần kết nối trước không thành công thì kết nối lại                           
       count=lost;
  
               
   while(digitalRead(12)==HIGH)
   {       
  delay(500); 
  Serial.println("wait...");
   }
  delay(1000); 
  Serial.println("SEND GET...update data ");                
  client.print(String("GET ")+ path + path_value + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection:keep-alive\r\n\r\n");
 
  delay(1000); // wait for server to respond
  
  // read response
  String section="header";
  while(client.available())
  {
     String line = client.readStringUntil('\r');
     Serial.print(line);
     count++;
  }
 
    
}// while
}// loop</span>