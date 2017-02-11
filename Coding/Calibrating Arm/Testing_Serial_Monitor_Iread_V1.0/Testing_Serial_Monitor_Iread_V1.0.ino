void setup() {
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  delay(2000);
}

char rx_byte = 0;
String rx_str = "";

void loop() {
  int val = 0;
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
    
    if (rx_byte != '\n') {
      // a character of the string was received
      rx_str += rx_byte;
    }
    else {
      int val = rx_str.toInt();
   }
  }
    if(rx_str.charAt(1) == '-'){
        val = -val;
    }
    rx_str = ""; 
    Serial.println(val);    
} // end: if (Serial.available() > 0)



int getInput(){
  char rx_byte = 0;
  String rx_str = "";
  int val;
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
    
    if (rx_byte != '\n') {
      // a character of the string was received
      rx_str += rx_byte;
    }
    else {
      val = rx_str.toInt();
      if(rx_str.charAt(1) == '-'){
        val = -val;      
      }        // clear the string for reuse
    }
    rx_str = ""; 
    //Serial.println(val);
    return val;    
  } // end: if (Serial.available() > 0)
}
