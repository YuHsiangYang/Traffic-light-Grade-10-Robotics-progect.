// C++ code
//
int num_pins[7] = {2, 3, 4, 5, 6, 7, 8};
int num = 0;
String data = "";
#include <Wire.h>
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
  for(int pin:num_pins){
    pinMode(pin, OUTPUT);
  }
  Wire.begin(7);
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);
}

void loop()
{
  /*
  for(int i = 10; i > 0; i--){
    writeDigit(i);
    delay(1000);
  }
  */
  writeDigit(num);
}
void receiveEvent(int howMany){
  num = Wire.read();
  Serial.println(num);
}
void writeDigit(int digit) {
  // Robojax Seven Segment Display for Arduino
  /*
  Serial.print(digit);
  Serial.print(" ");
  */
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