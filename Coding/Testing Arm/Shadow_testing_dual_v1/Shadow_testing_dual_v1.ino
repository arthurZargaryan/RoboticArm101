#include <Herkulex.h>

int knob0 = 0;
int knob1 = 1;
int knob2 = 2;
int knob3 = 3;

int val0;
int tempVal0;
int mapVal0;

int val1;
int tempVal1;
int mapVal1;

int val2;
int tempVal2;
int mapVal2;

int val3;
int tempVal3;
int mapVal3;

int motor0 = 0x00;
int motor1 = 0x01;
int motor2 = 0x02;
int motor3 = 0x03;

void setup(){
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.beginSerial1(115200); //open serial port 1 
  Herkulex.reboot(0xfe); //reboot first motor
 // Herkulex.reboot(motor2); //reboot second motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  
  // read status
  Serial.println("");
  Serial.print("Status1:"); 
  Serial.println(Herkulex.stat(motor0));
  Serial.print("Status2:"); 
  Serial.println(Herkulex.stat(motor1));
  Serial.print("Status1:"); 
  Serial.println(Herkulex.stat(motor2));
  Serial.print("Status2:"); 
  Serial.println(Herkulex.stat(motor3));

  delay(1000);
  Herkulex.setLed(motor0, LED_GREEN);
  Herkulex.setLed(motor1, LED_GREEN);
  Herkulex.setLed(motor2, LED_GREEN);
  Herkulex.setLed(motor3, LED_GREEN);
  delay(1000);
 }

void loop(){
  tempVal0 = analogRead(knob0);
  tempVal1 = analogRead(knob1);
  tempVal2 = analogRead(knob2);
  tempVal3 = analogRead(knob3);
  
  if( tempVal0 > val0 - 2 && tempVal0 < val0 + 2){
    tempVal0 = val0; 
  }
  if( tempVal1 > val1 - 2 && tempVal1 < val1 + 2){
    tempVal1 = val1; 
  }
  if( tempVal2 > val2 - 2 && tempVal2 < val2 + 2){
    tempVal2 = val2;
  } 
  if( tempVal3 > val3 - 2 && tempVal3 < val3 + 2){
    tempVal3 = val3; 
  }
  val0 = tempVal0;
  val1 = tempVal1;
  val2 = tempVal2;
  val3 = tempVal3;
  
  mapVal0 = map(val0, 0, 1023, -160, 160);
  mapVal1 = map(val1, 0, 1023, -160, 160);
  mapVal2 = map(val2, 0, 1023, -160, 160);
  mapVal3 = map(val3, 0, 1023, -160, 160);
  
  Serial.print("M0000 ");
  Serial.println(Herkulex.stat(motor0));
  Serial.print("M1111 ");
  Serial.println(Herkulex.stat(motor1));
  Serial.print("M2222 ");
  Serial.println(Herkulex.stat(motor2));
  Serial.print("M3333 ");
  Serial.println(Herkulex.stat(motor3));

  Herkulex.moveAllAngle(motor0, - mapVal0, 2);
  Herkulex.moveAllAngle(motor1, - mapVal1, 2);
  Herkulex.moveAllAngle(motor2, - mapVal2, 2); 
  //Herkulex.moveAllAngle(motor3, - mapVal3, 2);
  Herkulex.actionAll(100);
}

