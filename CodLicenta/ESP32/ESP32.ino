#include <WiFi.h>

const char* ssid = "ASUS_5G";
const char* password = "AsusNokia100"; 

TaskHandle_t task_loop1;
void esploop1(void* pvParameters) {
  setup1();

  for (;;)
    loop1();
}

void setup() {

 
  xTaskCreatePinnedToCore(
    esploop1,               /* Task function. */
    "loop1",                /* name of task. */
    10000,                  /* Stack size of task */
    NULL,                   /* parameter of the task */
    1,                      /* priority of the task */
    &task_loop1,            /* Task handle to keep track of created task */
    !ARDUINO_RUNNING_CORE); /* pin task to core */

}

void setup1() {
   Serial.begin(115200);
  delay(1000);
  WiFi.begin(ssid, password);
  while (!Serial) {
    delay(1);  // wait for serial port to connect.
  }
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void loop() {
  //Serial.printf("loop%d(): %d\n", xPortGetCoreID(), count0);
  delay(50);
}

void loop1() {
  //Serial.printf("loop%d(): %d\n", xPortGetCoreID(), count1);
  delay(50);
}
