/****************************
 *  FONCTION FACULTATIVE 1  *
 *     GROUPE 19 - RFID     *
 *      BOULILA Elyssa      *
 *     BOUZAIEN Mokhles     *
 *       THABET Achraf      *
 ****************************/

#include <Adafruit_NeoPixel.h>
#include <MFRC522.h>
#include <SPI.h>



const int      PIN       =  6; // Data output to Adafruit NeoPixel
const int      NUMPIXELS =  12; // Number of pixels in the ring ^
const int      SS_PIN    =  10; // Data PIN for MFRC522
const int      RST_PIN   =  9; // Reset PIN for MFRC522

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Defining colors
const uint32_t red       =  pixels.Color(255, 0, 0);
const uint32_t green     =  pixels.Color(0, 255, 0);
const uint32_t yellow    =  pixels.Color(255, 255, 0);
const uint32_t blank     =  pixels.Color(0, 0, 0);
const uint32_t white     =  pixels.Color(255, 255, 255);
const uint32_t blue      =  pixels.Color(0, 0, 255);


MFRC522 rfid(SS_PIN, RST_PIN); // Prepares PINS
MFRC522::MIFARE_Key key;


void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(7); // This is to make sure the lights won't burn up.
  SPI.begin(); // Make the NeoPixel and microcontroller communicate
  rfid.PCD_Init();
  setAll(white);
  
}

void loop() {
  int c = random(3);
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){
    return;
  }

  String strID = getID();    
  
  if(strID == "80:11:F7:73") {
    
    
    if (c == 0) {
      for (int i = 0; i<100; i+=2){
        setAll(white);
        pixels.setPixelColor(i%12, red);
        pixels.show();
        delay(100);
        setAll(white);
      }
    } else if (c == 1) {
      for (int i = 0; i<50; i+=1){
        setAll(white);
        pixels.setPixelColor(12-(i%12), blue);
        pixels.setPixelColor(i%16, green);
        pixels.show();
        delay(100);
        setAll(white);
      }
    } else if (c == 2) {
      pixels.setPixelColor(2, red);
      pixels.setPixelColor(3, red);
      pixels.setPixelColor(4, pixels.Color(237, 127, 16));
      pixels.setPixelColor(5, pixels.Color(237, 127, 16));
      pixels.setPixelColor(6, yellow);
      pixels.setPixelColor(7, yellow);
      pixels.setPixelColor(8, green);
      pixels.setPixelColor(9, green);
      pixels.setPixelColor(10, blue);
      pixels.setPixelColor(11, blue);
//      pixels.setPixelColor(12, pixels.Color(121, 28, 248));
//      pixels.setPixelColor(13, pixels.Color(121, 28, 248));
      pixels.setPixelColor(0, pixels.Color(102, 0, 153));
      pixels.setPixelColor(1, pixels.Color(102, 0, 153));
      pixels.show();
      delay(5000);
      setAll(white);
    }
  }
}

String getID() {
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }
  strID.toUpperCase();
  return strID;
}

void setAll(uint32_t color) {
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, color);
    pixels.show();
  }
}

