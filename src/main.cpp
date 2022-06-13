/*  
 Test the tft.print() viz embedded tft.write() function
 This sketch used font 2, 4, 7
 
 Make sure all the display driver and pin connections are correct by
 editing the User_Setup.h file in the TFT_eSPI library folder.
 Note that yield() or delay(0) must be called in long duration for/while
 loops to stop the ESP8266 watchdog triggering.
 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 */


#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define TFT_GREY 0x5AEB // New colour
#define Text_PADDING 45
#define poti_pin 35
#define regulate_pin 25
bool running = false;
int poti_value;
int poti_value_old;
int temp_value;

const int temp_preheat = 150;
const int temp_reflow = 240;

void publishText(const char* text, const int x, const int y, bool forceRefresh = false){
  if(forceRefresh){
    tft.fillScreen(TFT_BLACK);
  }
  tft.drawString(text, x, y);
}

void regulate_temp(int current_temp, int temp_target, int offset) {
  if (temp_target <= current_temp - offset) {
    digitalWrite(regulate_pin, LOW);
  }
  else if (temp_target > current_temp + offset) {
    digitalWrite(regulate_pin, HIGH);
  }
}

void setup(void) {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}



void loop() {
  poti_value = map(analogRead(poti_pin), 4095, 0, temp_preheat, temp_reflow);
  tft.setTextSize(2);
  if(digitalRead(26) == 1){
    running = true;
  }
  if(running){
    if(poti_value >= temp_value){
      publishText("REFLOWED", 0, Text_PADDING,false);
      running = false;
    }else{
      regulate_temp(temp_value,poti_value,0);
      publishText("REFLOWING", 0, Text_PADDING,false);
    } 
  }
  else{
    if(temp_value == 150){
      publishText("PREHEATED", 0, Text_PADDING,false);
    }else{
      publishText("PREHEATING", 0, Text_PADDING,false);
    }
    regulate_temp(temp_value,150,0);
  }

  Serial.println(poti_value);
  publishText("C_Temp: ",0, 0,false);
  publishText(String(poti_value).c_str(), 100, 0,false);
  publishText("S_Temp: ",0, 20,false);
  publishText(String(0).c_str(), 100, 20,false);
  poti_value_old = poti_value;
  delay(100);

  }