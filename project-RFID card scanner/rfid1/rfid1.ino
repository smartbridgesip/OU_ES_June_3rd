
#include <SPI.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

constexpr uint8_t RST_PIN = 5;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 4; // Configurable, see typical pin layout above
int led=2;
int buzzer=13;


 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

void setup() { 
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}
  

void loop() {
  int arr[]={152,159,24,59};

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
     

  }
 


  if (rfid.uid.uidByte[0] == arr[0] || 
    rfid.uid.uidByte[1] == arr[1] || 
    rfid.uid.uidByte[2] == arr[2] || 
    rfid.uid.uidByte[3] == arr[3] ) {
    Serial.println(F("Access Granted."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      arr[i] = rfid.uid.uidByte[i];
    }
    digitalWrite(led,HIGH);
    delay(3000);
    digitalWrite(led,LOW);
    
}
  else {
    Serial.println(F("Access denied."));
     digitalWrite(buzzer,HIGH);
     delay(3000);
     digitalWrite(buzzer,LOW);
     

  }
 


  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
