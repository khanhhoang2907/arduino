/****** Thong tin ********************
written by Linh Kiện TCP
Linh Kiện TCP – số 70/ngõ 40, Tạ Quang Bửu, Hai Bà Trưng, Hà Nội.
Web: Linhkientcp.vn
Fb : https://www.facebook.com/linhkienTCP/
Bán hàng: 0966.129.629                 Kỹ thuật: 01663.860.326

***************************/


/**** Giới thiệu code ***************
 *  Code sử dụng biến giới hạn là 25 cm để xác định khoảng cách cần dừng.
 *  Khi ta muốn thay đổi khoảng cách, ta thay đổi tham số "gioihan" đang để mặc định là 25. ( đơn vị cm)
 *  Xe ưu tiên rẽ trái trong các trường  hợp phía trước có vật cản. 
 *  Ví dụ: khi khoang cách phía trước <25 , cảm biến đo bên trái trước, nếu không có vật cản thì xe rẽ trái. nếu bên trái cũng có vật cản
 *  lúc đó xe mới kiểm tra bên phải.
 *  Khi cả phía trước, trái ,phải đều có chướng ngại vật. xe đi lùi 1 đoạn, sau đó đo lại khoảng cách. ....
 */

#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
/******** khai báo chân input/output**************/

const int trig = 6;     // chân trig của SRF-05.
const int echo = 5;     // chân echo của SRF-05.
int tien1=10;           // chân IN - A của Module L298.
int tien2=11;           // chân IN - C của Module L298.
int lui1=12;            // chân IN - D của Module L298.
int lui2=13;            // chân IN - B của Module L298.
int dongcoservo=9;      // chân Orange của Servo.

int gioihan = 25;
int i;
int x=0;
unsigned long thoigian; // biến đo thời gian
int khoangcach;           // biến lưu khoảng cách
int khoangcachtrai,khoangcachphai;

void dokhoangcach();
void dithang(int duongdi);
void disangtrai();
void disangphai();
void dilui();
void resetdongco();
void quaycbsangphai();
void quaycbsangtrai();
void setup() {
  // put your setup code here, to run once:
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
    
    pinMode(tien1,OUTPUT); 
    pinMode(tien2,OUTPUT); 
    pinMode(lui1,OUTPUT); 
    pinMode(lui2,OUTPUT); 
    digitalWrite(tien1,LOW);
    digitalWrite(tien2,LOW);
    digitalWrite(lui1,LOW);
    digitalWrite(lui1,LOW);
   // Serial.begin(9600);
    myservo.write(90);    
    delay(500);
   
    
    
}

void loop() 
{   
    khoangcach=0;
    dokhoangcach();
    if(khoangcach>gioihan||khoangcach==0) 
    {
      dokhoangcach();
       if(khoangcach>gioihan||khoangcach==0) 
        {
          dithang();   
        }   
    }
    else
    {
      
      resetdongco();
      quaycbsangtrai();
      
      khoangcachtrai=khoangcach;
     
      quaycbsangphai();
      khoangcachphai=khoangcach;
      if(khoangcachphai<10&&khoangcachtrai<10){
        dilui();
      }
      else
      {
        if(khoangcachphai>khoangcachtrai) 
        {
          disangtrai();
          delay(500);
        }
        if(khoangcachphai<khoangcachtrai) 
        {
          disangphai();
          delay(500);
        }
      }
    }
  //Serial.println(khoangcach);
}




void dithang()
{ 
  
    
        digitalWrite(tien1,HIGH);
        digitalWrite(tien2,HIGH);
        //delay(2);
   
}

void disangtrai()
{
  resetdongco();
  digitalWrite(lui1,HIGH);
  delay(250);
  digitalWrite(lui1,LOW);
  
    
}
void disangphai()
{
   resetdongco();
  digitalWrite(lui2,HIGH);
  delay(250);
  digitalWrite(lui2,LOW);
  
}

void dilui()
{
  resetdongco();
  for(i=0;i<20;i++)
    
        digitalWrite(lui1,HIGH);
        digitalWrite(lui2,HIGH);
        delay(700);
     
    digitalWrite(lui1,LOW);
    digitalWrite(lui2,LOW);
}

void resetdongco()
{
  digitalWrite(tien1,LOW);
  digitalWrite(tien2,LOW);
  digitalWrite(lui1,LOW);
  digitalWrite(lui2,LOW);
}
/******** chương trình đo khoảng cách SRF04 ***************/
void dokhoangcach()
{
/* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(10);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    thoigian = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    khoangcach = int(thoigian/2/29.412);
    

}

/*********** chương trình quay cảm biến xang trái *********/
void quaycbsangtrai()
{
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(1000);
    dokhoangcach();
    myservo.write(90);              // tell servo to go to position in variable 'pos'  
}
void quaycbsangphai()
{
    myservo.write(0);              // tell servo to go to position in variable 'pos'
    delay(1000);
    dokhoangcach();
    myservo.write(90);              // tell servo to go to position in variable 'pos'
}
void resetservo()
{
   myservo.write(90);
}


