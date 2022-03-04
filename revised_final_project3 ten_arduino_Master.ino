// C++ code
//
#include <Wire.h>
int num_pins[7] = {2, 3, 4, 5, 6, 7, 8};
int num = 0;
byte displayLEDs[10][7] = { 
        { 0,0,0,0,0,0,1 },  // = 0
        { 1,0,0,1,1,1,1 },  // = 1
        { 0,0,1,0,0,1,0 },  // = 2
        { 0,0,0,0,1,1,0 },  // = 3
        { 1,0,0,1,1,0,0 },  // = 4
        { 0,1,0,0,1,0,0 },  // = 5
        { 0,1,0,0,0,0,0 },  // = 6
        { 0,0,0,1,1,1,1 },  // = 7
        { 0,0,0,0,0,0,0 },  // = 8
        { 0,0,0,0,1,0,0 }   // = 9     
        }; 
void setup()
{
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  for(int pin:num_pins){
    pinMode(pin, OUTPUT);
  }
}

void loop()
{
  
  for(int i = num; i >= 0; i--){
    display_number(i);
    delay(1000);
  }
  
  
}

void display_number(int number){
  Wire.beginTransmission(7);
   // Serial.println(number);
    Wire.write(number % 10);
    Wire.endTransmission();
    writeDigit(number/10);
}
void receiveEvent(int howMany){
  num = Wire.read();
}
void writeDigit(int digit) {
  // Robojax Seven Segment Display for Arduino
  //Serial.print(digit);
  //Serial.print(" ");
  if(digit == 10){
    digit = 0;
  }
   int digitValue;
  for (int i=0; i < 7; i++) 
  {

      digitalWrite(num_pins[i], convertHighLow(displayLEDs[digit][i]));// write the HGIH or LOW (depending on the type) to output pin
      //Serial.print(convertHighLow(displayLEDs[digit][i]));// print the result to the Serial monitor

  }// for i
}//writeDigit ends here


int convertHighLow(int v)
{
  int convertedValue;
    if(v ==0)
    {
      convertedValue = 1 ;// if common anode, change the HIGH to LOW and LOW to HIGH
    }else{
      convertedValue = 0;// if common cathode, keep it the same
    } 

    return convertedValue;
}