const int trigpin1=2;
const int echopin1=4;
const int trigpin2=12;
const int echopin2=14;
  int Buzzer=5;
 long duration1;
 int distance1;
 long duration2;
 int distance2;
 void ultrasonic1();
 void ultrasonic2();
 void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(trigpin1,OUTPUT);
pinMode(echopin1,INPUT);
pinMode(trigpin2,OUTPUT);
pinMode(echopin2,INPUT);
pinMode(Buzzer,OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  ultrasonic1();
  ultrasonic2();
}
 void ultrasonic1(){
digitalWrite(trigpin1,LOW);
delayMicroseconds(2);
digitalWrite(trigpin1,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin1,LOW);
duration1=pulseIn(echopin1,HIGH);
distance1=duration1*0.034/2;
Serial.print("distance1=");
Serial.println(distance1);
if(distance1>=60 || distance1==  0)
{
Serial.println("no object detected");
digitalWrite(Buzzer,LOW);
}
else
{
  Serial.println("object detected \n");
  Serial.print("distance1= ");
  Serial.print(distance1);
  digitalWrite(Buzzer,HIGH);
}
 }
void ultrasonic2(){
  digitalWrite(trigpin2,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin2,LOW);
  duration2=pulseIn(echopin2,HIGH);
  distance2=duration2*0.034/2;
  
Serial.print("distance2=");
Serial.println(distance2);

  if(distance2>=60 || distance2==0)
{
Serial.println("no object detected");
digitalWrite(Buzzer,LOW);
}
else
{
  Serial.println("object detected \n");
  Serial.print("distance2= ");
  Serial.print(distance2);
  digitalWrite(Buzzer,HIGH);
}
}
