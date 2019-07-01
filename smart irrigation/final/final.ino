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
int i1=0,u1=0,m1=0;

WiFiServer server(80);

void setup()  
{  
  
  Serial.begin(115200);
  pinMode(33,INPUT);
  //pinMode(18,OUTPUT);
  pinMode(21,INPUT);
  pinMode(19,OUTPUT);
  //pinMode(5,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
   
    
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
  server.begin();  
}  
void loop()   
{  

  static boolean data_state = false;
  i1=IRsensor();
  u1= ultrasonic();
  m1=MOISTsensor();

  WiFiClient client = server.available();
   
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  
    client.println("Refresh: 10"); 
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("<p style='text-align: center;'><span style='font-size: x-large;'><strong>SMART IRRIGATION</strong></span></p>");
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>IR sensor= ");
    client.println(i1);
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>ULTRASONIC = ");
    client.println(u1);
    client.print("<p style='text-align: center;'><span style='color: #0000ff;'><strong style='font-size: large;'>MOISTURE = ");
    client.println(m1);
    client.print("</p>");
    client.println("</html>");
    
  
  
}
  
int IRsensor()
  {
  
  b=digitalRead(21);
  
  Serial.println(b);
  if(b==1)
    digitalWrite(19,LOW);
  else
    digitalWrite(19,HIGH);
  
  ThingSpeak.writeField(myChannelNumber, 1, b, myWriteAPIKey);
  return b;
} 
  int MOISTsensor()
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
  return a; 
  }
int ultrasonic()
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
  return distance;
}
