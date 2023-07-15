#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219_A(0x40);
Adafruit_INA219 ina219_B(0x41);
Adafruit_INA219 ina219_C(0x44);
Adafruit_INA219 ina219_D(0x45);

void setup(void) 
{
  Serial.begin(115200);

  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  if (! ina219_A.begin()&&!ina219_B.begin()&&!ina219_C.begin()&&!ina219_D.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }

  Serial.println("Measuring voltage and current with INA219's ...");
}

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;


void loop(void) 
{
  
  shuntvoltage = ina219_A.getShuntVoltage_mV();
  busvoltage = ina219_A.getBusVoltage_V();
  current_mA = ina219_A.getCurrent_mA();
  power_mW = ina219_A.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("A  A  Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("A  A  Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("A  A  Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("A  A  Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("A  A  Power:         "); Serial.print(power_mW); Serial.println(" mW");
  delay(50);
  shuntvoltage = ina219_B.getShuntVoltage_mV();
  busvoltage = ina219_B.getBusVoltage_V();
  current_mA = ina219_B.getCurrent_mA();
  power_mW = ina219_B.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("B  B  Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("B  B  Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("B  B  Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("B  B  Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("B  B  Power:         "); Serial.print(power_mW); Serial.println(" mW");
delay(50);
  shuntvoltage = ina219_C.getShuntVoltage_mV();
  busvoltage = ina219_C.getBusVoltage_V();
  current_mA = ina219_C.getCurrent_mA();
  power_mW = ina219_C.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("C  C  Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("C  C  Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("C  C  Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("C  C  Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("C  C  Power:         "); Serial.print(power_mW); Serial.println(" mW");
  delay(50);
  shuntvoltage = ina219_D.getShuntVoltage_mV();
  busvoltage = ina219_D.getBusVoltage_V();
  current_mA = ina219_D.getCurrent_mA();
  power_mW = ina219_D.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  Serial.print("D  D  Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("D  D  Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("D  D  Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("D  D  Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("D  D  Power:         "); Serial.print(power_mW); Serial.println(" mW");

  delay(30000);
}