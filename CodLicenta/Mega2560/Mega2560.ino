#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP280.h"
#include <SPI.h>
#include <SD.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;


File myfile;

const int pinCS = 53;//pin chipselect micro SD
int StatusComutatorExtern=13;

#define PIN            6  //pin neopixeli pentru controlul lor 
#define NUMPIXELS      61 //numarul de leduri 

#define SCREEN_WIDTH 128 // latime OLED
#define SCREEN_HEIGHT 64 // inaltime OLED

#define OLED_RESET     -1 // pin de reset, nefiind prezent reset-ul se face o data cu arduino-ul
#define SCREEN_ADDRESS 0x3D // 0x3D pentru 128x64p - prenzent in proiect , si 0x3C pentru 128x32p , majoritatea OLED-urilor permit schimbarea intre cele 2 adrese I2C printr-un jumper
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);//declararea vectorului de leduri

Adafruit_BMP280 bmp;//initializarea senzorului de temperatura si presiune 

Adafruit_INA219 ina219_0x40(0x40);// Control circuit                     -dreapta              -FUNCTIONAL      NO contacts bridged      |
//Adafruit_INA219 ina219_B(0x41);//panou cablu lung-bridge A0         -langa presetupe      -trilulilu       bridge A0                |-----> module pentru contorizare energie produsa.
Adafruit_INA219 ina219_0x44(0x44);//panou cablu scurt-bridge A1          - mijloc              -FUNCTIONAL      bridge A1                |
//Adafruit_INA219 ina219_D(0x45);//load 2 panou mobil                  -stanga              -unresponsive    full bridge A0&A1        |


unsigned long long int prev_time_10ms   = 0;                          //--
unsigned long long int prev_time_50ms   = 0;                          //----
unsigned long long int prev_time_100ms  = 0;                          //------
unsigned long long int prev_time_1s     = 0;                          //--------
unsigned long long int prev_time_5s     = 0;                          //---------- declarare valori pentru task-uri 
unsigned long long int prev_time_1m     = 0;                          //--------
unsigned long long int prev_time_5m     = 0;                          //------
unsigned long long int prev_time_1h     = 0;                          //----
unsigned long long int actual_time      = 0;                          //--

#define task_10ms        10                                           //--
#define task_50ms        50                                           //-----
#define task_100ms      100                                           //--------
#define task_1s        1000                                           //----------definire valori pentru recurenta
#define task_5s        5000                                           //--------
#define task_1m       60000                                           //------
#define task_5m      300000                                           //----
#define task_1h     3600000                                           //--
//=============================================================================Control Motoare BTS7960
int motor1Len=4;
int motor1Ren=5;
int motor1R_PWM=6;
int motor1L_PWM=7;

int motor2Len=8;
int motor2Ren=9;
int motor2R_PWM=10;
int motor2L_PWM=11;
//=============================================================================Control Motoare 

//============================================================Vectori pentru filtrarea datelor provenite de la senzori
const int nrSamples_INA219=10;                
int indexSample=0;

int achizitii_0x40_mW[nrSamples_INA219];
int total_0x40_mW=0;

int achizitii_0x44_mW[nrSamples_INA219];
int total_0x44_mW=0;

double achizitii_0x40_mA[nrSamples_INA219];
double total_0x40_mA=0;

double achizitii_0x44_mA[nrSamples_INA219];
double total_0x44_mA=0.0;

double achizitii_0x40_V[nrSamples_INA219];
double total_0x40_V=0.0;

double achizitii_0x44_V[nrSamples_INA219];
double total_0x44_V=0.0;
//===========================================================
sensors_event_t humidity, temp;

double pressure;
double temperature;

double shuntvoltage_0x40 = 0;
double busvoltage_0x40 = 0;
double current_mA_0x40 = 0;
double loadvoltage_0x40 = 0;
double power_mW_0x40 = 0;

double shuntvoltage_0x44 = 0;
double busvoltage_0x44 = 0;
double current_mA_0x44 = 0;
double loadvoltage_0x44 = 0;
double power_mW_0x44 = 0;

int alarmaTemperatura=0;
int pinReleuVentESP=24;
int pinReleuVentIna219=25;
int pinReleu3=23;
int pinReleu4=24;
int pinSelectOLED=26;

int cursor=0;

//====================================================================Fotorezistori
int adc1=A8;
int adc2=A9;
int adc3=A10;
int adc4=A11;

int punct1 =0;
int punct2 =0;
int punct3 =0;
int punct4 =0;
//====================================================================
void setup(void) 
{
  //Serial.begin(115200);//comnicarea seriala cu PC-ul
  
  pinMode(pinCS, OUTPUT);//punul pentru activarea cardului microSD
  if (SD.begin(53))//incepe comunicarea cu modulul microSD
  {
    //Serial.println("SD card is ready to use.");
  } else
  {
    //Serial.println("SD card initialization failed");
    return;
  }
  
  pinMode(pinReleuVentESP,OUTPUT);
  pinMode(pinReleuVentIna219,OUTPUT);
  pinMode(pinReleu3,OUTPUT);
  pinMode(pinReleu4,OUTPUT);
  pinMode(pinSelectOLED,INPUT);
  
  if(digitalRead(pinSelectOLED) == HIGH){
    digitalWrite(pinReleuVentESP,HIGH);
  }else{
    digitalWrite(pinReleuVentESP,LOW);
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
  }
  display.setTextColor(SSD1306_WHITE);

  pinMode(StatusComutatorExtern,INPUT);//pinul 13, legat pentru probe la un switch intre GND si 5V
  strip.begin();
  strip.show();

  ina219_0x40.begin();
  //ina219_B.begin();//senzor ars
  ina219_0x44.begin();
  //ina219_D.begin();//senzor ars
  bmp.begin();//bmp280 - preniune si temperatura
  aht.begin();//aht21 - temperatura si umiditate aer

  if (! ina219_0x40.begin()/*||!ina219_B.begin()*/||!ina219_0x44.begin()/*||!ina219_D.begin()*/) {//verific daca cel putin un chip INA219 este functional
    //Serial.println("Failed to find INA219 chip");// initial credeam ca aici se ajunge doar daca sunt deconectate liniile de I2C ...
    while (1) { delay(10); }
  }
  //=============================================================================Control Motoare BTS7960
  pinMode(  motor1Len    ,OUTPUT);
  pinMode(  motor1Ren    ,OUTPUT);
  pinMode(  motor1R_PWM  ,OUTPUT);
  pinMode(  motor1L_PWM  ,OUTPUT);
  pinMode(  motor2Len    ,OUTPUT);
  pinMode(  motor2Ren    ,OUTPUT);
  pinMode(  motor2R_PWM  ,OUTPUT);
  pinMode(  motor2L_PWM  ,OUTPUT);
  digitalWrite(motor1Len    ,LOW); 
  digitalWrite(motor1Ren    ,LOW); 
  digitalWrite(motor1R_PWM  ,LOW); 
  digitalWrite(motor1L_PWM  ,LOW); 
  digitalWrite(motor2Len    ,LOW); 
  digitalWrite(motor2Ren    ,LOW); 
  digitalWrite(motor2R_PWM  ,LOW); 
  digitalWrite(motor2L_PWM  ,LOW); 
  //=============================================================================Control Motoare
}



void loop(void) 
{

  actual_time=millis();
  if(actual_time-prev_time_10ms>=task_10ms){
    func_10ms();
    prev_time_10ms=actual_time;
  }
  if(actual_time-prev_time_50ms>=task_50ms){
    func_50ms();
    prev_time_50ms=actual_time;
  }
  if(actual_time-prev_time_100ms>=task_100ms){
    func_100ms();
    prev_time_100ms=actual_time;
  }
  if(actual_time-prev_time_1s>=task_1s){
    func_1s();
    prev_time_1s=actual_time;
  }
  if(actual_time-prev_time_5s>=task_5s){
    func_5s();
    prev_time_5s=actual_time;
  }
  if(actual_time-prev_time_1m>=task_1m){
    func_1m();
    prev_time_1m=actual_time;
  }
  if(actual_time-prev_time_5m>=task_5m){
    func_5m();
    prev_time_5m=actual_time;
  }
  if(actual_time-prev_time_1h>=task_1h){
    func_1h();
    prev_time_1h=actual_time;
  }

}

//shuntvoltage = ina219_B.getShuntVoltage_mV();
  //busvoltage = ina219_B.getBusVoltage_V();
  //current_mA = ina219_B.getCurrent_mA();
  //power_mW = ina219_B.getPower_mW();
  //loadvoltage = busvoltage + (shuntvoltage / 1000);
  //
  //Serial.print("B  B  Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  //Serial.print("B  B  Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  //Serial.print("B  B  Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  //Serial.print("B  B  Current:       "); Serial.print(current_mA); Serial.println(" mA");
  //Serial.print("B  B  Power:         "); Serial.print(power_mW); Serial.println(" mW");
  //Serial.println("");

//shuntvoltage = ina219_D.getShuntVoltage_mV();
  //busvoltage = ina219_D.getBusVoltage_V();
  //current_mA = ina219_D.getCurrent_mA();
  //power_mW = ina219_D.getPower_mW();
  //loadvoltage = busvoltage + (shuntvoltage / 1000);
  //
  //Serial.print("D  D  Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  //Serial.print("D  D  Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  //Serial.print("D  D  Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  //Serial.print("D  D  Current:       "); Serial.print(current_mA); Serial.println(" mA");
  //Serial.print("D  D  Power:         "); Serial.print(power_mW); Serial.println(" mW");
  //Serial.println("");

//if(digitalRead(StatusComutatorExtern)==HIGH){
  //colorWipe(strip.Color(255, 0, 0)); // Red
  //colorWipe(strip.Color(0, 255, 0)); // Green
  //colorWipe(strip.Color(0, 0, 255)); // Blue
  //}else{
  //  colorWipe(strip.Color(0,0,0)); 
  //}

//void colorWipe(uint32_t color) {
//  for(int i=0; i<strip.numPixels(); i++) {
//    strip.setPixelColor(i, color);
//    strip.show();
//  }
//}