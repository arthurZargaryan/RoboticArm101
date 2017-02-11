#include <Herkulex.h>

int motorNew = 0x01; // new id you want motor to have

void setup(){
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.beginSerial2(115200); //open serial port 1 
  Herkulex.reboot(0xfe); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  Herkulex.setLed(motorNew, LED_BLUE);
  // Herkulex.moveSpeedOne(motorNew, 500, 1000, LED_CYAN);
  //Herkulex.moveOne(motorNew, 0, 1500, LED_BLUE);
  Serial.println(Herkulex.stat(motorNew));
  Serial.println(Herkulex.getPosition(motorNew));
  Herkulex.torqueOFF(motorNew);
  Serial.println("Torque off");

}

void loop(){
  Serial.println(Herkulex.getPosition(motorNew));
  Serial.println(Herkulex.stat(motorNew));
  delay(1000);
}

