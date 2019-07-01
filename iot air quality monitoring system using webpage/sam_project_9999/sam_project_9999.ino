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


#define LED 2
#define SENSOR 33 
#define DELAY 500
#include <ThingSpeak.h>

int threshold=200;
int sensorValue = 0;
int gas;     // variable to store the value coming from the sensor
const char* ssid     = "SmartBridge"; 
const char* password = "smartbridge@sb";

WiFiClient client;

unsigned long myChannelNumber = 805724; 
const char *myWriteAPIKey ="JFQLRDW7YOO6FV02";

WiFiServer server(80);
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Sensor start");
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
    ThingSpeak.begin(client);
}

void loop() {
  
  // read the value from the sensor:
   sensorValue = analogRead(SENSOR);
  Serial.print("Value: "); Serial.println(sensorValue);
  if (sensorValue==200) {
    digitalWrite(LED,HIGH);}
    else
    digitalWrite(LED,LOW);
  
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(DELAY);
  ThingSpeak.writeField(myChannelNumber, 1,  sensorValue, myWriteAPIKey);
    delay(30000);
  
  WiFiClient client = server.available();
   
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  
    client.println("Refresh: 10"); 
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>Digital Air quality </strong></span></p>");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>GAS (ppm)= ");
   client.println( sensorValue);
    client.println("</html>");
    delay(5000);
    static boolean data_state = false;
    
   
    
}
