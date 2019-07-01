#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>


constexpr uint8_t RST_PIN = 5;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 4;     // Configurable, see typical pin layout above
static const int servoPin = 21;    //servo motor output

Servo servo1;
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

int arr_b[] = {219,218,138,53};
int arr_a[] = {203,57,99,54};


void setup() { 
  pinMode(2,OUTPUT);         //green bulb
  pinMode(14,OUTPUT);       //red bulb when it is denined
  pinMode(22,OUTPUT);       //red bulb standard
  Serial.begin(9600);
  servo1.attach(servoPin);
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
  digitalWrite(22,HIGH);

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
    digitalWrite(22,LOW);
    delay(2);
    digitalWrite(2,HIGH);
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(1);
    }
    delay(3000);
    digitalWrite(2,LOW);
    delay(2);
    digitalWrite(22,HIGH);
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(1);
    }
    }
    else if (rfid.uid.uidByte[0] == arr_b[0] &&
    rfid.uid.uidByte[1] == arr_b[1] &&
    rfid.uid.uidByte[2] ==arr_b[2] &&
    rfid.uid.uidByte[3] == arr_b[3] ) 
    {
    Serial.println(F("GRANTED."));
    digitalWrite(2,HIGH);
    delay(2);
    digitalWrite(22,LOW);
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(1);
    }
    delay(3000);
    digitalWrite(2,LOW);
    delay(2);
    digitalWrite(22,HIGH);
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(1);
    }
    }
   
  else 
  {Serial.println(F("DENINED"));
  digitalWrite(14,HIGH);
  delay(2);
  digitalWrite(22,HIGH);
  delay(3000);
  digitalWrite(14,LOW);
  delay(2);
  digitalWrite(22,HIGH);
  }
  

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
