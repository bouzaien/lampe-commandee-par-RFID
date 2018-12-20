/****************************
 *  FONCTION OBLIGATOIRE 6  *
 *     GROUPE 19 - RFID     *
 *      BOULILA Elyssa      *
 *     BOUZAIEN Mokhles     *
 *       THABET Achraf      *
 ****************************/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void setup() {
        Serial.begin(9600);        // Initialize serial communications with the PC
        SPI.begin();               // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
        Serial.println(F("Write personal data on a MIFARE PICC "));
}

void loop() {
        
        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        MFRC522::MIFARE_Key key;
        for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
        
        // Look for new cards
        if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){
          return;
        }
        
        Serial.print(F("Card UID:"));    //Dump UID
        for (byte i = 0; i < mfrc522.uid.size; i++) {
          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(mfrc522.uid.uidByte[i], HEX);
        } 
        Serial.print(F(" PICC type: "));   // Dump PICC type
        MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
        Serial.println(mfrc522.PICC_GetTypeName(piccType));
         
        byte buffer[34];  
        byte block;
        MFRC522::StatusCode status;
        byte len;
        
        Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
        // Ask personal data: full name
        Serial.println(F("Write your full name ending with #"));
        len = Serial.readBytesUntil('#', (char *) buffer, 30) ; // read full name from serial
        for (byte i = len; i < 30; i++) buffer[i] = ' ';     // pad with spaces
        
        block = 16;
        //Serial.println(F("Authenticating using key A..."));
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
           Serial.print(F("PCD_Authenticate() failed: "));
           Serial.println(mfrc522.GetStatusCodeName(status));
           return;
        }
        else Serial.println(F("PCD_Authenticate() success: "));
        
        // Write block
	status = mfrc522.MIFARE_Write(block, buffer, 16);
	if (status != MFRC522::STATUS_OK) {
	    Serial.print(F("MIFARE_Write() failed: "));
	    Serial.println(mfrc522.GetStatusCodeName(status));
            return;
	}
        else Serial.println(F("MIFARE_Write() success: "));


        Serial.println(" ");
        mfrc522.PICC_HaltA(); // Halt PICC
        mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
       
}
