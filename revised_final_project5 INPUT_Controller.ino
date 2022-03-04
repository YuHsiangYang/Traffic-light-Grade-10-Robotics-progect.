// C++ code
//
#include <Wire.h>
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {7, 6, 5, 4};
String data = "";
bool green_red = false; //false = green true = red
bool complete = false;
bool stop = false;
int green = 0;
int red = 0;
bool stopped = false;
Keypad num_pad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  char key = num_pad.getKey();
  if (key && key != '*' && key != '#') {
    data += key;
    char content [data.length() + 1];
    data.toCharArray(content, data.length() + 1);
    Wire.beginTransmission(2);
    for (char con : content) {
      Wire.write(con);
    }
    Wire.endTransmission();

    Serial.println(data);
  }
  else if (key == '*' && green == 0) {
    // char green[50];
    green = data.toInt();
    Serial.println(green);
    data += " Sec green";
    //data.toCharArray(green, 50);
    Wire.beginTransmission(2);
    for (char te : data) {
      Wire.write(te);
    }
    Wire.endTransmission();
    data = "";
    Serial.println(green);
    green_red = true;
  }
  else if (key == '*' && green > 0 && red == 0) {
    // char red[50];
    red = data.toInt();
    Serial.println(red);
    data += " Sec red";
    //data.toCharArray(red, 50);
    Wire.beginTransmission(2);
    for (char te : data) {
      Wire.write(te);
    }
    Wire.endTransmission();
    Serial.println(red);
    data = "";
  }
  else if (key == '#' && stop == false) {
    //data = "Start";
    //send data to lcd arduino
    Wire.beginTransmission(2);
    Wire.write("Start");
    stop = true;
    Wire.endTransmission();
    //send data to controller arduino
    Wire.beginTransmission(3);
    String time_green_red = "Start" + String(green) + " " + String(red);
    for (char te : time_green_red) {
      Wire.write(te);
    }
    Wire.endTransmission();
    Serial.println(time_green_red);
    complete = true;
    delay(500);
  }
  else if (stop == true) {
    Wire.requestFrom(3, 32);
      stopped = Wire.read();
      if (stopped == true && stop == true) {
        Wire.beginTransmission(2);
        Wire.write("Light stopped");
        Wire.endTransmission();
        delay(1000);
        
data = "";
green_red = false; //false = green true = red
complete = false;
stop = false;
green = 0;
red = 0;
        
        Wire.beginTransmission(2);
        Wire.write("clear");
        Wire.endTransmission();
      }
    else if(key == '#' && stopped == false){
      char text[50];
    //data = "Stop";
    //send data to lcd arduino
    Wire.beginTransmission(2);
    Wire.write("Stop");
    Wire.endTransmission();
    //send reset
    /*
      Wire.beginTransmission(3);
      Wire.write("Reset");
      Wire.endTransmission();
    */
    //send data to controller arduino
    
    Wire.beginTransmission(3);
    Wire.write("Stop");
    Wire.endTransmission();

    Wire.beginTransmission(2);
    Wire.write("Stopping");
    Wire.endTransmission();
    delay(500);
    }
    delay(500);
  }
}