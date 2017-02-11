#include <Herkulex.h>

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

  Herkulex.torqueOFF(0xfe);
  delay(1000);
  Herkulex.setLed(motor0, LED_GREEN);
  Herkulex.setLed(motor1, LED_GREEN);
  Herkulex.setLed(motor2, LED_GREEN);
  Herkulex.setLed(motor3, LED_GREEN);
  delay(1000);
 }

void loop(){
  Serial.print("M0000 ");
  Serial.println(Herkulex.getAngle(motor0));
  Serial.print("M1111 ");
  Serial.println(Herkulex.getAngle(motor1));
  Serial.print("M2222 ");
  Serial.println(Herkulex.getAngle(motor2));
  Serial.print("M3333 ");
  Serial.println(Herkulex.getAngle(motor3));
}

