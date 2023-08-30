// C++ code
//
#define LED_Green 4
#define LED_Red 2
#define LED_Blue 3
#include <Wire.h>
void setup()
{
  Wire.begin(3);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Blue, OUTPUT);
  Serial.begin(9600);
}
String state = "";
String data = "";
int green = 0;
int red = 0;
bool written = false;
bool stop = false;
bool stopped = false;

bool start_sended = false;
void loop()
{
  if(data == "Stop" && stopped == false){
    Wire.beginTransmission(5);
    for(char ch:data){
      Wire.write(ch);
    }
    Wire.endTransmission();
    analogWrite(LED_Red, 255);
    analogWrite(LED_Green, 255);
    analogWrite(LED_Blue, 0);
    Wire.requestFrom(5, 32);
    stopped = Wire.read();
    if(stopped == true){
      analogWrite(LED_Red, 255);
      analogWrite(LED_Green, 0);
      analogWrite(LED_Blue, 0);
      stopped = false;
    }
    Serial.println(stopped);
  }
  else if(data.indexOf('Start') != -1 && data != "Stop"){
    //turn light to green
    analogWrite(LED_Red, 0);
    analogWrite(LED_Green, 255);
    analogWrite(LED_Blue, 0);
    
    //Wire.begin();
    Wire.beginTransmission(5);
    for(char ch:data){
      Wire.write(ch);
    }
    Wire.endTransmission();
    Serial.println(data);
    start_sended = true;
  }
  Serial.println(data);
  delay(400); // Delay a little bit to improve simulation performance
}
void requestEvent(){
  Wire.write(stopped); 
}
void receiveEvent(int howMany){
  data = "";
  while( Wire.available()){
    data += (char)Wire.read();
    
  }
  Serial.println(data);
}