#include<SoftwareSerial.h>
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(1,FUNCTION_3);
}


void loop() {
  if(digitalRead(1)==1)
  {
  digitalWrite(LED_BUILTIN, HIGH); 
  }
  else                  
  digitalWrite(LED_BUILTIN, LOW);   
                     
}
