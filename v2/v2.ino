#include <DHT.h>
#define dht_apin A0 // Analog Pin sensor is connected to

//L293D
//Motor A
const int motorPin1  = 4;  // Pin 14 of L293
const int motorPin2  = 5;  // Pin 10 of L293
//Motor B
const int motorPin3  = 6; // Pin  7 of L293
const int motorPin4  = 7;  // Pin  2 of L293

const int trigPin = 8;
const int echoPin = 12;
long duration;
int distance;
dht DHT;
int data = 0;
int d1=0;  
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, Tx
void setup()
{
   pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600);
    mySerial.begin(38400);//Sets the baud for serial data transmission                               
    pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
    pinMode(3, INPUT);
     
    
}
void loop()
{
  DHT.read11(dht_apin);
  int d2=DHT.humidity;
  int d3=DHT.temperature;
  d3=d3+100;
  data = digitalRead(3);
  data=data+200;
   if (mySerial.available() > 0)      // Send data only when you receive data:
   {
      d1 = mySerial.read();        //Read the incoming data & store into data
     // Serial.print(d1);
      //Print Value inside data in Serial monitor     
     if(d1 >= 200)
      {d1=d1-200;
        if(d1 == 0)              // Checks whether value of data is equal to 1
         {Serial.print("Smoke");
         digitalWrite(13, HIGH);   //If value is 1 then LED turns ON
         Serial.print("\n");}
      else if(d1 == 1)         //  Checks whether value of data is equal to 0
        {  Serial.print("No Smoke");
          digitalWrite(13, LOW);    //If value is 0 then LED turns OFF
          Serial.print("\n");}
     }
    else if(d1 < 200 && d1> 100)
      {d1=d1-100;
       Serial.print("Temp.=");
       Serial.print(d3);
     Serial.print("\n");}
     else
      {
       Serial.print("Humidity=");
       Serial.print(d2);
     Serial.print("\n");
     Serial.print("\n");}
   delay(500);
   }
   mySerial.write(data);
   mySerial.write(d2);
   mySerial.write(d3);

}

