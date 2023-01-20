/*
  Arduino RFID Keyboard 

  This little code shows you how easy you can use a RFID Modul in combination with a Keyboard function (from Arduino Pro Micro (ATmega32U4)).
  Freely usable for all with the exception of military and other anti-social activities.
  Created 22.8.2015 by Marc-André Tragé
  
  Pinout for Arduino Pro Micro
  ! VCC  to RFID RC522 Modul needs 3.3v, more informations about this at line 22.
    GND  GND
    IRG  not connected
    RST  pin 5
    SDA  pin 10  
    MISO pin 14
    SCK  pin 15  
    MOSI pin 16

  What you need for a little RFID fun:
    +  Arduino Pro Micro and Leonardo or equal Boards with a ATmega32U4
       it can emulate via USB a keyboard or a mouse) order types like this => https://www.google.de/search?q=arduino+pro+micro
    +  RFID RC522 Modul like this => https://www.google.de/search?q=rfid+rc522
    +  if you have only 5.0v VCC on Board, use a AMS1117-3.3 like this => http://www.advanced-monolithic.com/pdf/ds1117.pdf
    
  If you have any useful changes or improvements please let me know.
  (Not a wish (but a command)) have fun (NOW (and for the rest of your life))!

  
  https://github.com/MTrage/Arduino-RFID-Keyboard/blob/master/Arduino-RFID-Keyboard.ino

  ++++++++++++++++++    Edit for Special use by EsMi 20 Jan 2023
*/


// ATmega32U4 Boards needs this include for USB output (keyboard / mouse)
   #include <Keyboard.h>

// BEG RFID module Part
   #include <SPI.h>
   #include <MFRC522.h>
   #define SS_PIN  10
   #define RST_PIN 5
   MFRC522 mfrc522(SS_PIN, RST_PIN);
   String RFID_Key;
   int UpperCase = 0;

void setup(){
  
  // RFID Modul
  SPI.begin();
  mfrc522.PCD_Init();
  
  }




void loop(){

// Is there to find an RFID card?
  if ( ! mfrc522.PICC_IsNewCardPresent()){
    return;
    }
    
  if ( ! mfrc522.PICC_ReadCardSerial()){
    return;
    }
  
// If an RFID card has been scanned, then the id will be assembled
  String RFID = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    RFID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
    RFID.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

      RFID.toUpperCase();
      RFID_Key=RFID.substring(1);
      delay(100);
      Keyboard.print(RFID_Key);
      delay(100);
      Keyboard.press(KEY_TAB);          // press and TAB
      delay(100);
      Keyboard.releaseAll();           // release both
      RFID_Key = "0";                 // Flush MEM
      delay(5000);                     // 
  }
