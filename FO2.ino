/****************************
 *  FONCTION OBLIGATOIRE 2  *
 *     GROUPE 19 - RFID     *
 *      BOULILA Elyssa      *
 *     BOUZAIEN Mokhles     *
 *       THABET Achraf      *
 ****************************/

#include <Adafruit_NeoPixel.h> // NeoPixel library import
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int     PIN          =  6;
const int     NUMPIXELS    =  12;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// defining colors
const uint32_t red       =  pixels.Color(255, 0, 0);
const uint32_t green     =  pixels.Color(0, 255, 0);
const uint32_t yellow    =  pixels.Color(255, 255, 0);
const uint32_t blank     =  pixels.Color(0, 0, 0);
const uint32_t white     =  pixels.Color(255, 255, 255);
const uint32_t blue      =  pixels.Color(0, 0, 255);

void setup() {
  pixels.begin(); // initializes NeoPixel
}

void loop() {
  pixels.setPixelColor(0, red);
  pixels.setPixelColor(6, blue);
  pixels.show();
  delay(1000);
  setAll(blank);
  delay(1000);
}

// set a unique color to all pixels
void setAll(uint32_t color) {
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, color);
    pixels.show();
  }
}
