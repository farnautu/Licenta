#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP280.h"
#include <SPI.h>
#include <SD.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int chipSelect = 53;//pin chipselect micro SD
int statusLeduri=13;

#define PIN            6  //pin neopixeli
#define NUMPIXELS      60 //numarul de leduri 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_BMP280 bmp;
Adafruit_INA219 ina219_A(0x40);//Arduino,esp-no contacts bridged  -dreapta
Adafruit_INA219 ina219_B(0x41);//panou cablu lung-bridge A0 -  langa presetupe
Adafruit_INA219 ina219_C(0x44);//panou cablu scurt-bridge A1- mijloc
Adafruit_INA219 ina219_D(0x45);//load 2 panou mobil -full bridge A0&A1 -stanga

void setup(void) 
{
Serial.begin(115200);

  //display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();

  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();

  pinMode(statusLeduri,INPUT);
strip.begin();
strip.show();

  
    
    ina219_A.begin();
    ina219_B.begin();
    ina219_C.begin();
    ina219_D.begin();
    bmp.begin();
  Serial.println("Hello!");
  /*if (! ina219_A.begin()&&!ina219_B.begin()&&!ina219_C.begin()&&!ina219_D.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }*/

  Serial.println("Measuring voltage and current with INA219's ...");
}
float pressure;
float temperature;

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;


void loop(void) 
{
  if(digitalRead(statusLeduri)==HIGH){
  colorWipe(strip.Color(255, 0, 0), 5); // Red
  colorWipe(strip.Color(0, 255, 0), 5); // Green
  colorWipe(strip.Color(0, 0, 255), 5); // Blue
  }else{
    colorWipe(strip.Color(0,0,0), 0); 
  }
  pressure = bmp.readPressure();
	temperature = bmp.readTemperature();
  Serial.print(F("Pressure: "));
    Serial.print(pressure);
    Serial.print(" Pa");
    Serial.print("\t");
    Serial.print(("Temp: "));
    Serial.print(temperature);
    Serial.println();
  //=======================================================================================================INA219
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
  Serial.println("");
  
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
  Serial.println("");
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
  Serial.println("");
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
  Serial.println("");
  //======================================================================================================INA219

  display.clearDisplay();
	display.setCursor(0,0);
	display.setTextSize(1);
	display.println("Full");
	display.display();
  delay(2000);
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}