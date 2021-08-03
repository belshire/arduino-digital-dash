#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object

static float afrValue = 0;
int AFR_PIN = A0;
int AFR_DISPLAY_MIN = 9;
int AFR_DISPLAY_MAX = 19;

float mapf(float val, float in_min, float in_max, float out_min, float out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    bool resistorsOnSegments = 0; 
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);
}
void loop() {
  // Read afr pin map values
  // 0V =  9.0
  // 5V = 19.0
  afrValue = analogRead(AFR_PIN);
  float mapAFRPin = mapf(afrValue, 0, 1023, AFR_DISPLAY_MIN, AFR_DISPLAY_MAX);
  
  // Display float as an int multiply by 10 and set display with decimal point at 1 in setNumber
  int mapAFRPinInt = static_cast<int>(mapAFRPin*10);
  sevseg.setNumber(mapAFRPinInt,1);

  sevseg.refreshDisplay(); // Must run repeatedly
}
