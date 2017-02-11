#include <Herkulex.h>
// remeber only give pos between 1002 and 21. The recomended range
int motorNew = 0x04; // new id you want motor to have

void setup(){
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.beginSerial2(115200); //open serial port 1 
  Herkulex.reboot(0xfe); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors 
  Herkulex.setLed(0xfe,LED_GREEN); //set the led
  delay(500); 
  Herkulex.torqueOFF(0xfe);
  Serial.print("Motor 0 status: ");
  Serial.println(Herkulex.stat(0));
  Serial.print("Motor 1 status: ");
  Serial.println(Herkulex.stat(1));
  Serial.print("Motor 2 status: ");
  Serial.println(Herkulex.stat(2));
  Serial.print("Motor 3 status: ");
  Serial.println(Herkulex.stat(3));
  Serial.print("Motor 4 status: ");
  Serial.println(Herkulex.stat(4));
}

void loop(){
  Serial.print("Motor 0 position: ");
  Serial.println(Herkulex.getPosition(0));
  Serial.print("Motor 1 position: ");
  Serial.println(Herkulex.getPosition(1));
  Serial.print("Motor 2 position: ");
  Serial.println(Herkulex.getPosition(2));
  Serial.print("Motor 3 position: ");
  Serial.println(Herkulex.getPosition(3));
  Serial.print("Motor 4 position: ");
  Serial.println(Herkulex.getPosition(4));
  delay(5000);
}

