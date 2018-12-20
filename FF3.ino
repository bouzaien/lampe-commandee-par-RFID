/****************************
 *  FONCTION FACULTATIVE 3  *
 *     GROUPE 19 - RFID     *
 *      BOULILA Elyssa      *
 *     BOUZAIEN Mokhles     *
 *       THABET Achraf      *
 ****************************/

#include <Wire.h> // for communiction with I2C
#include <LiquidCrystal_I2C.h> // I2C library import
#include <MFRC522.h> // RFID library import
#include <SPI.h> //Serial Peripheral Interface

const int      SS_PIN    =  10; // Data PIN for MFRC522
const int      RST_PIN   =  9; // Reset PIN for MFRC522
String         msg[4]    =  {"Message 1", "Message 2", "Message 3", "Message 4"};

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display
MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 inctance
MFRC522::MIFARE_Key key;


void setup()
{
  Serial.begin (9600);
  SPI.begin();
  lcd.init(); // initialize the lcd 
  lcd.backlight(); // turn on backlight
  rfid.PCD_Init(); // initialize the rfid
}

void loop()
{
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){
    return;
  }
  String strID = getID(); // save the badge ID
  printText(strID, random(4)); // print text depending on the badge
}

// function to print texxt depending on the card
void printText(String usercard, int i) {
  if (usercard == "B0:D4:4E:80" || usercard == "80:11:F7:73") {
      lcd.setCursor(0,0);
      lcd.print(msg[i]);
      delay(2000);
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

