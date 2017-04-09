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

  delay(1000);
  Serial.println("CLEAR area robot STARTING-UP in 5 seconds");
  delay(5000);
  Herkulex.moveAll(0x00, 630, LED_BLUE);  
  Herkulex.moveAll(1, 540, LED_BLUE); 
  Herkulex.moveAll(2, 160, LED_BLUE); 
  Herkulex.moveAll(3, 520, LED_BLUE); 
  Herkulex.moveAll(4, 710, LED_BLUE); 
  Herkulex.actionAll(1000);
}

void loop(){

  /*Serial.println(Herkulex.getPosition(0));
  Serial.print("Motor 1 status: ");
  Serial.println(Herkulex.getPosition(1));
  Serial.print("Motor 2 status: ");
  Serial.println(Herkulex.getPosition(2));
  Serial.print("Motor 3 status: ");
  Serial.println(Herkulex.getPosition(3));
  Serial.print("Motor 4 status: ");
  Serial.println(Herkulex.getPosition(4));  
  delay(5000);*/

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
  delay(5000);
  
}

