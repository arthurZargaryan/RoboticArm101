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
  renameMotor(); // The serial monitor should print New motor set ID: "new ID" afterwhich there should be a zero. If Not then rerun the program it will usually work after the second attempt
}

void loop(){
  Serial.println(Herkulex.stat(motorNew));
  Serial.println(Herkulex.getPosition(motorNew));
  delay(3000);
}

void renameMotor(){
  int motorDefault = findMotor();
  Herkulex.setLed(motorDefault,LED_GREEN); //set the led 
  delay(1000);
  Herkulex.set_ID(motorDefault, motorNew);
  Herkulex.reboot(motorNew); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  Herkulex.setLed(motorNew, LED_BLUE);

  Herkulex.moveOne(motorNew, 512, 1500, LED_BLUE);
  Serial.print("New Motor set to ID: ");
  Serial.println(motorNew);
  Serial.println(Herkulex.stat(motorNew));
  Serial.println(Herkulex.getPosition(motorNew));
  delay(3000);
  
  
}

int findMotor(){
  if(Herkulex.stat(0xfd)== 0){
      Serial.print(" Motor found with ID: 0XFD (Default ID)");
      delay(3000);
      return 0xfd;
    }
    
  for (int i = 0; i<255; i++) {
    Serial.println(i);
    if(Herkulex.stat(i)== 0){
      Serial.print("Motor found with ID: ");
      Serial.println(i);
      delay(3000);
      return i;
    }
  }
}



  

