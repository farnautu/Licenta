#include <Wire.h>
void setup() {
  Serial.begin (115200);

  Serial.println ();
  byte DeviceCout = 0;
  
  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      DeviceCout++;
      } 
  }
  Serial.println ("Finish.");
  Serial.print ("Dispozitive gasite: ");
  Serial.print (DeviceCout, DEC);
} 

void loop() {}