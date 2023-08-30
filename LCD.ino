// C++ code
//
#include <LiquidCrystal.h>
#include <Wire.h>
#include<stdio.h>
#include <stdlib.h>
const int rs = 8;
const int en = 7;
const int d4 = 3;
const int d5 = 4;
const int d6 = 5;
const int d7 = 6;
String data = "";
String pre_data = "";
int red_sec = 0;
int green_sec = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  Wire.begin(2);
  Serial.begin(9600);
  Wire.onReceive(receiveEvent); 
}
bool next_line = false;
void loop()
{
  /*
  lcd.setCursor(0, 1);
  lcd.print("123");
  */
  if(data == "Start"){
    lcd.clear();
    lcd.print(data);
    delay(200);
  }
  else if(data == "clear"){
    lcd.clear();
    next_line = false;
    //lcd.print("stoping lights");
  }
  else if(data != pre_data && next_line == false){
    lcd.clear();
    lcd.print(data);
    
    pre_data = data;
    green_sec = data.toInt();
    if(data.indexOf('green') != -1){
      next_line = true;
      Serial.println(next_line);
    }
    delay(200);
  } // Delay a little bit to improve simulation performance
  else if(next_line == true && data.indexOf('green') == -1){
    lcd.setCursor(0, 1);
    lcd.print(data);
  }
  else if(data.indexOf('Start') != -1){
    lcd.clear();
    lcd.print(data);
    Serial.println(data);
  }
  else if(data.indexOf('Stop') != -1){
    lcd.clear();
    lcd.print("Stop");
    Serial.println(data);
  }
  delay(100);
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
    Serial.println(data);
  }
}