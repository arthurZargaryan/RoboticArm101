#include <Herkulex.h>
#include <math.h>
#include "Arduino.h"

//For serial inuting
char rx_byte =0;
String rx_str = "";

//Motors Value
int motor0 = 0x00;

//Coordinates
float x = 0;
float y = 0;
float z = 0;

//Rotation Values
int angleBase = 0;

//Position Values
int positionBase = 0;

//flags
boolean input = false;

//Thresholds
int baseLowerThreshold = 21;
int baseUpperThreshold = 1002;

void setup(){
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.beginSerial1(115200); //open serial port 1 
  Herkulex.reboot(0xfe); //reboot Motors
  delay(500); 
  Herkulex.initialize(); //initialize motors
  
  // read status
  Serial.println("");
  Serial.print("Status1:"); 
  Serial.println(Herkulex.stat(motor0));

  delay(1000);
  Herkulex.setLed(motor0, LED_GREEN);
  delay(1000);
 }

void loop(){
  Serial.print("Status1:"); 
  Serial.println(Herkulex.stat(motor0));
  
  getBaseAngle();
  Serial.print("Angle:"); 
  Serial.println(angleBase);
  Serial.print("Position:"); 
  Serial.println(positionBase);
  Herkulex.moveAll(motor0, positionBase, 2);
  Herkulex.actionAll(300);
}

int getBaseAngle(){
  getCoordinates();
  angleBase = atan2(x, y)*180/PI;
  Serial.print("Raw angle: ");
  Serial.println(angleBase);
  if(angleBase > 159){
    angleBase = 159;
    Serial.println("Angle too large");
  }
  else if(angleBase < -159){
    angleBase = -159;
    Serial.println("Angle too small");
  }
  positionBase =  map(angleBase, -159, 159, 20, 1002);
  delay(3000);
}

void getCoordinates(){
  String coord = getInput();
  if(input){
    if(coord.indexOf('x')>-1 && coord.indexOf('y')>-1 && coord.indexOf('z')>-1){
      int i = coord.indexOf('x');
      String xPos = "";
      delay(4000);
      i++;
      while(coord.charAt(i) != ' ' && i < coord.length()){
        xPos += coord.charAt(i);
        i++;
      }
      x = xPos.toFloat();      
      i = coord.indexOf('y');
      String yPos = "";
      i++;
      while(coord.charAt(i) != ' ' && i < coord.length()){
        yPos += coord.charAt(i);
        i++;
      }
      y = yPos.toFloat(); 
      i = coord.indexOf('z');
      String zPos = "";
      i++;
      while(coord.charAt(i) != ' ' && i < coord.length()){
        zPos += coord.charAt(i);
        i++;
      }
      z = zPos.toFloat(); 
      Serial.println("_________________");
      Serial.print("X: ");
      Serial.print(x);
      Serial.print(" Y: ");
      Serial.println(y);    
      Serial.print(" Z: ");
      Serial.println(z); 
    }
    else{
      Serial.println("Input needs to contain x and y, in lower case");
      Serial.println("followed by their respective values and eperated by a space");
      Serial.println("i.e: x100 y300");
      delay(3000);
    }
  }
}


String getInput(){
  if(Serial.available() > 0){
    rx_str = "";// clear the string for reuse
    while (Serial.available() > 0) {    // is a character available?
      input = true;
      rx_byte = Serial.read();       // get the character
      if (rx_byte != '\n') {
        // a character of the string was received
        rx_str += rx_byte;
      }
      else {
        return rx_str;
               // clear the string for reuse
      }      
    }
  }
  input = false;  
  return rx_str;
}
