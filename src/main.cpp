#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello world!");
}

void loop() {
  // put your main code here, to run repeatedly:
}