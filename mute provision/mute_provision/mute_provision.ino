
int sensorPin1 = A0;
int sensorPin2 = A1;
// select the input pin for the potentiometer
int ledPin = 13; 
int buzzer = 8;// select the pin for the LED
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16,2);
 Serial.begin(9600); 
}

void loop() {
  // read the value from the sensor:
  sensorValue1 = analogRead(sensorPin1);
  
  Serial.print("sensorValue1:");
  Serial.println(sensorValue1);
  delay(500);
  sensorValue2 = analogRead(sensorPin2);
  
  Serial.print("sensorValue2:");
  Serial.println(sensorValue2);
 delay(500);
   


  delay(500);
  lcd.clear();

  if(sensorValue1<240){
    
    lcd.print("water");
    Serial.println("Water");
    
    
    }    

    if(sensorValue2<=240){
      
      lcd.print("food");
    Serial.println("food");
    digitalWrite(buzzer,HIGH);
    delay(500);
    //lcd.setCursor(0,1);
    digitalWrite(buzzer,LOW);
    
    
    
    
    }
     if(sensorValue1>=241&&sensorValue2>=241)
    {
      
      lcd.print("rest room");
    Serial.println("rest room");
    digitalWrite(buzzer,HIGH);
    delay(500);
    //lcd.setCursor(0,1);
    digitalWrite(buzzer,LOW);
    
    }
    
}
