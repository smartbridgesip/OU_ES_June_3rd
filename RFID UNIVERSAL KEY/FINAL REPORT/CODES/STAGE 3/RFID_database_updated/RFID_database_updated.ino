#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <SPI.h>

const char* ssid     = "Sarma"; 
const char* password = "vector103";
WiFiClient client;
WiFiServer server(80);


constexpr uint8_t RST_PIN = 5;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 4;     // Configurable, see typical pin layout above
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];
int arr_c[] = {203,185,242,54};     //data of the pre saved card
int arr_b[] = {219,218,138,53};
int arr_a[] = {203,57,99,54};
int arr_d[] = {58,252,13,63}; 

void setup() { 
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi is connected");
    server.begin();
    Serial.println("Server started");
    Serial.println(WiFi.localIP());
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
 // Serial.print(F("Using the following key:"));
//  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
 
void loop() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print("PICC type: ");
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
    WiFiClient client = server.available();
   
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  
    client.println("Refresh: 10"); 
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>UNIVERSAL RFID</strong></span></p>");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>Name:<pre>P NAGA LAKSHMI NARAYANA SARMA ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>PH.no:<pre>7530027881 ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>D.O.B:<pre>18/12/1997 ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>SEX:<pre>MALE ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>FATHER NAME:<pre> S JAGANNADHA RAO ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>ADDRESS:FLAT NO:<pre>435 KALPKRITI PARISAR,RISALI, BHILAI,CHHATTISGARH. ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>OCCUPATION:<pre>STUDENT ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>INSTTUTION:<pre> KARUNYA INSTITUTE OF TECHNOLOGY AND SCIENCES.");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>INSTITUTION ID:<pre> UR16EC077");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>AADHAR CARD NO:<pre>7944 0195 5822 ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>DRIVING LICENCE NUMBER:<pre>CG07 20160010527 ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>VEHICLE CLASS:<pre>LMV , MCWG ");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>DATE OF ISSUE:<pre> 21/7/2016");
    client.print("<p style='text-align: side;'><span style='color: #0000ff;'><strong style='font-size: large;'>DRIVING LICENCE VALIDITY:<pre>20/7/2036");
    client.print("</p>");
    client.println("</html>");
    delay(50);
    }
    else if (rfid.uid.uidByte[0] == arr_b[0] &&
    rfid.uid.uidByte[1] == arr_b[1] &&
    rfid.uid.uidByte[2] ==arr_b[2] &&
    rfid.uid.uidByte[3] == arr_b[3] ) 
    {
   // Serial.println(F("GRANTED."));
   WiFiClient client = server.available();
   
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  
    client.println("Refresh: 10"); 
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>MOBILE INFORMATION LOG</strong></span></p>");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>User name:       Gausic ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Company  :       LENOVO");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Mobile Number:   8220757658 ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Model name:      VIBE K5 note ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Price:           12000 Rs ");
    client.print("</p>");
    client.println("</html>");
    delay(50);
    }
    else if (rfid.uid.uidByte[0] == arr_c[0] &&
    rfid.uid.uidByte[1] == arr_c[1] &&
    rfid.uid.uidByte[2] ==arr_c[2] &&
    rfid.uid.uidByte[3] == arr_c[3] ) 
    {
   // Serial.println(F("GRANTED."));
   WiFiClient client = server.available();
   
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  
    client.println("Refresh: 10"); 
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>MOBILE INFORMATION LOG</strong></span></p>");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>User name:       Esther ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Company  :       NOKIA ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Mobile Number:   9488601946 ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Model name:      3 ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Price:           9500 Rs ");
    client.print("</p>");
    client.println("</html>");
    delay(50);
    }
    else if (rfid.uid.uidByte[0] == arr_d[0] &&
    rfid.uid.uidByte[1] == arr_d[1] &&
    rfid.uid.uidByte[2] == arr_d[2] &&
    rfid.uid.uidByte[3] == arr_d[3] ) 
    {
    Serial.println(F("GRANTED."));
    WiFiClient client = server.available();
   
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  
    client.println("Refresh: 10"); 
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>MOBILE INFORMATION LOG</strong></span></p>");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>User name:       Swathi ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Company  :       HONOR");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Mobile Number:   8085746851 ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Model name:      9lite ");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>Price:           11500 Rs ");
    client.print("</p>");
    client.println("</html>");
    delay(50);
    }
  else Serial.println(F("DENINED"));
  
  

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
