/****************************
 *  FONCTION FACULTATIVE 2  *
 *     GROUPE 19 - RFID     *
 *      BOULILA Elyssa      *
 *     BOUZAIEN Mokhles     *
 *       THABET Achraf      *
 ****************************/

#include <Adafruit_NeoPixel.h> // NeoPixel library import
#include <MFRC522.h> // RFID library import
#include <SPI.h> //Serial Peripheral Interface



const int      PIN       =  6;  // Data output to Adafruit NeoPixel
const int      NUMPIXELS =  12; // Number of pixels in the ring ^
const int      SS_PIN    =  10; // Data PIN for MFRC522
const int      RST_PIN   =  9;  // Reset PIN for MFRC522

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Defining colors
const uint32_t red       =  pixels.Color(255, 0, 0);
const uint32_t green     =  pixels.Color(0, 255, 0);
const uint32_t yellow    =  pixels.Color(255, 255, 0);
const uint32_t blank     =  pixels.Color(0, 0, 0);
const uint32_t white     =  pixels.Color(255, 255, 255);
const uint32_t blue      =  pixels.Color(0, 0, 255);


MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 inctance
MFRC522::MIFARE_Key key;


void setup() {
  SPI.begin();
  Serial.begin (9600);
  rfid.PCD_Init();
  pixels.begin();
  pixels.setBrightness(7);
  setAll(white);
  
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){
    return;
  }

  String strID = getID();  
    
  String ch;  
  MFRC522::StatusCode status;
      
  Serial.setTimeout(5000L) ;
  Serial.println(F("Choose a color (red, blue green)"));
  ch=Serial.readString();
  if(strID == "B0:D4:4E:80") {
    if (ch == "red"){
      setAll(red);
      delay(2000);
      setAll(white);
    } else if (ch == "blue") {
      setAll(blue);
      delay(2000);
      setAll(white);
    } else if (ch == "green") {
      setAll(green);
      delay(2000);
      setAll(white);
    } else {
      Serial.println("Invalid Color :(");
    }
  }
  
}

// function to read th card ID
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

// set a unique color to all pixels
void setAll(uint32_t color) {
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, color);
    pixels.show();
  }
}
