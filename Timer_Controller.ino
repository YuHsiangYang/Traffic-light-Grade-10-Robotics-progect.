// C++ code
//
#include <Wire.h>
#define LED_Green 4
#define LED_Yellow 3
#define LED_Red 2
#define Buzzer A0
void setup()
{
  Wire.begin(5);
  Wire.onReceive(receiveEvent); 
  Wire.onRequest(requestEvent);
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Yellow, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);
}
int red = 0;
int green = 0;
String data = "";
bool stop = false;
void loop()
{
  if(data == "Stop" && stop == false){
    Serial.println("Traffic light stoped");
    stop = true;
  }
  else if(data && red != 0 && green != 0){
    traffic_light(green ,red);
    stop = false;
  }
}

void requestEvent(){
  Wire.write(stop);
}

void receiveEvent(int howMany){
/*
x = Wire.read();
  
  if (x == 1){
  
        digitalWrite(pinLed,HIGH);
  }
  else{
        digitalWrite(pinLed,LOW);
  }
  Serial.println(x);
  */
  data = "";
  while( Wire.available()){
    data += (char)Wire.read();
  }
  Serial.println(data);
  green = data.substring(5, data.indexOf(' ')).toInt();
  red = data.substring(data.indexOf(' '), data.length()).toInt();
}
void traffic_light(int green, int red){
  for(int i = green; i >= 0; i--){
    //Serial.println(i);
    tone(Buzzer, 6000);
    delay(50);
    noTone(Buzzer);
    digitalWrite(LED_Green, HIGH);
    Wire.begin();
    Wire.beginTransmission(9);
    Wire.write(i);
    Wire.endTransmission();
    
    delay(950);
  }
  digitalWrite(LED_Green, LOW);
  tone(Buzzer, 1000);
    delay(500);
    noTone(Buzzer);
  digitalWrite(LED_Yellow, HIGH);
  delay(1000);
  digitalWrite(LED_Yellow, LOW);
  digitalWrite(LED_Red, HIGH);
  for(int i = red; i >= 0; i--){
    tone(Buzzer, 6000);
    delay(50);
    noTone(Buzzer);
    Wire.begin();
    Wire.beginTransmission(9);
    Wire.write(i);
    Wire.endTransmission();
    delay(1000);
  }
  digitalWrite(LED_Red, LOW);
}