#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 5;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 4;     // Configurable, see typical pin layout above
int a=0;              //counter for a
int b=0;              //counter for c
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];
int arr_c[] = {203,185,242,54};     //data of the pre saved card

int arr_a[] = {203,57,99,54};

void setup() { 
  Serial.begin(9600);
  pinMode(12,OUTPUT);    //leb bulb
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
 
void loop() {

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

  if (rfid.uid.uidByte[0] == arr_a[0] &&
    rfid.uid.uidByte[1] == arr_a[1] &&
    rfid.uid.uidByte[2] ==arr_a[2] &&
    rfid.uid.uidByte[3] == arr_a[3] ) 
    {
      
    Serial.println(F("GRANTED."));
    if(a%2==0)
    {
      digitalWrite(12,HIGH);
    }
    else{
      digitalWrite(12,LOW);}
      a++;
    }
   
    else if (rfid.uid.uidByte[0] == arr_c[0] &&
    rfid.uid.uidByte[1] == arr_c[1] &&
    rfid.uid.uidByte[2] ==arr_c[2] &&
    rfid.uid.uidByte[3] == arr_c[3] ) 
    {
    Serial.println(F("GRANTED."));
     if(b%2==0)
    {
      digitalWrite(12,HIGH);
    }
    else{
      digitalWrite(12,LOW);}
      b++;
    }
   
  else Serial.println(F("DENINED"));
  
  

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
  
