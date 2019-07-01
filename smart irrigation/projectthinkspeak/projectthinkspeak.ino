#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
 
#include <ThingSpeak.h>  
  
const char* ssid = "SmartBridge";  
const char* password = "smartbridge@sb";  
WiFiClient client;  
 long myChannelNumber = 804381;  
const char * myWriteAPIKey = "DCUMD18HPKL1H2XI"; 
int a;
int b;
const int trigPin=2;
const int echoPin=4;
long duration;
int distance;

void setup()  
{  
  pinMode(33,INPUT);
  //pinMode(18,OUTPUT);
  pinMode(21,INPUT);
  pinMode(19,OUTPUT);
  //pinMode(5,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(115200);  
    
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  } 
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}  
void loop()   
{  
  static boolean data_state = false;
  IRsensor();
  ultrasonic();
  MOISTsensor();
}
  
void IRsensor()
  {
  b=digitalRead(21);
  Serial.println(b);
  if(b==1)
    digitalWrite(19,LOW);
  else
    digitalWrite(19,HIGH);
  
  ThingSpeak.writeField(myChannelNumber, 1, b, myWriteAPIKey);
} 
  void MOISTsensor()
  {
  a=analogRead(33);  
  Serial.println(a); 
  if(a>600   && a<=2500)
    digitalWrite(19,LOW);
    
  else
    digitalWrite(19,HIGH);
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to field 1. 
   ThingSpeak.writeField(myChannelNumber, 3, a, myWriteAPIKey);  
  
  //delay(30000); // ThingSpeak will only accept updates every 15 seconds.  
  }
void ultrasonic()
{
 
   
  digitalWrite(trigPin,LOW);      
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;
  Serial.print("Distance");
  Serial.println(distance);
  if(distance>5   && distance<=20)
    digitalWrite(19,HIGH);
    
  else
    digitalWrite(19,LOW);
  ThingSpeak.writeField(myChannelNumber, 2, distance, myWriteAPIKey); 
}
