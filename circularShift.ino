#include <Adafruit_NeoPixel.h>



#define PIN 6
#define SOFTPOT_PIN A0

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(15, PIN, NEO_GRB + NEO_KHZ800);
int sensorValue = 0;

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// How many LED's there are and rainbow definition
const int LED_L = 15;
int red[LED_L] = { 100, 255, 255,   0,   0,   0, 255, 255, 255, 255,   0,   0,   0, 255, 255};
int green[LED_L]= {100,  0,   0,   0, 255, 255, 255, 150,   0,   0,   0, 255, 255, 255, 180};
int blue[LED_L] = {100,  0, 255, 255, 255,   0,   0,   0,   0, 255, 255, 255,   0,   0,   0};

void setup() {
  strip.begin();
  strip.setBrightness(40);
  strip.show(); // Initialize all pixels to 'off'
  for (int i = 0; i < LED_L; i++){
    strip.setPixelColor(i, 
      strip.Color(red[i],green[i],blue[i]));
  }
}

int range = 1024/3;
int min_val = 1024/3;

void loop() {
  sensorValue = (analogRead(SOFTPOT_PIN) - min_val) * 3;
  for (int i = 0; i < LED_L; i++){
    strip.setPixelColor(i, 
      strip.Color(red[i],green[i],blue[i]));
  }
  shiftLeft();
  
  strip.show();
  delay(1000);
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void shiftLeft(){
  for (int i = 0; i < LED_L; i++){
    if (i == 0){
      red[LED_L-1] = red[0];
      blue[LED_L-1] = blue[0];
      green[LED_L-1] = green[0];
    }
    red[i] = red[i + 1];
    blue[i] = blue[i + 1];
    green[i] = green[i + 1];
  }
}

void shiftRight(){
  for (int i = LED_L; i > 0; i--){
    if ( i == (LED_L-1) ){
      red[0] = red[LED_L-1];
      green[0] = green[LED_L-1];
      blue[0] = blue[LED_L-1];
      //continue;
    }
    red[i] = red[i - 1];
    blue[i] = blue[i - 1];
    green[i] = green[i - 1];
  }
}
