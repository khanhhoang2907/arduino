#include<iostream>
using namespace std;




int distan =0;
int khanh(){
  int a=4;
  int b=a +distan;
  return b;
}
int ly(){
     int c=5;
     int h =c+ distan;
     return h;
}
int main(){
  if(khanh()>ly()){
    cout<<"Hole"<<endl;
  }
}