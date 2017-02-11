#include <Herkulex.h>
int n=0xfe; //motor ID - verify your ID !!!!

void setup()  
{
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.beginSerial1(115200); //open serial port 1 
  Herkulex.reboot(n); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  

  Serial.println("Get servo Angle");
  Serial.println(Herkulex.getAngle(n));
  delay(1200);
  Serial.println("Move to zero");
  Herkulex.moveOneAngle(n, 0, 300, LED_BLUE); //move motor with 300 speed  
  delay(1000);
  Serial.print("Get servo Angle:");
  Serial.println(Herkulex.getAngle(n));
}

void loop(){  
  delay(1200);
  Serial.print("Get servo 1 Angle:");
  Serial.println(Herkulex.getAngle(0xfd));
  Serial.print("Get servo 2 Angle:");
  Serial.println(Herkulex.getAngle(2));
}


