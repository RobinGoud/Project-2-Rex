#include <Wire.h>
// Sensor Rex is de code voor de sensoren van auto rex, rex is de passenger rescue bot
int trigPin1 = 3; 
int echoPin1 = 2; 
int trigPin2 = 5;
int echoPin2 = 4;
int irSensor1 = 6;
int irSensor2 = 7;


bool obstacel;
bool ravijn;
bool stoppen;
bool correctieLinks;
bool correctieRechts;
bool bocht;

long duration1, afstand1, duration2, afstand2;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  Wire.begin(9); 
  Wire.onRequest(requestEvent);
  
  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  

  
}
 
void loop() {
  obstacel = sonar2();
  Serial.print("obstacel: ");
  Serial.println(obstacel);
  ravijn = sonar1();
  Serial.print("Ravijn: ");
  Serial.println(ravijn);
  
  
    //-----------------------------------------------------------------------------
  if(digitalRead(irSensor1) == false){ //Als er een lijn wordt gedetecteerd
    correctieLinks = true;
    }
  else
  {
    correctieLinks = false;
  }
    Serial.print("CorrectieLinks: ");
     Serial.println(correctieLinks);
   //------------------------------------------------------------------------------
  if(digitalRead(irSensor2) == false){ //Als er een lijn wordt gedetecteerd
    correctieRechts = true;
    }
  else
  {
    correctieRechts = false;
  }
    Serial.print("Correctie Rechts: ");
    Serial.println(correctieRechts);
  


}

bool sonar1(){
    
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
 

  duration1 = pulseIn(echoPin1, HIGH);
  afstand1 = (duration1 / 2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  
  if(afstand1 > 10){
    return true;
    }
  else{
    return false;
    }
}
bool sonar2(){
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
 

  duration2 = pulseIn(echoPin2, HIGH);
  afstand2 = (duration2 / 2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  
  if(afstand2 < 10){
    return true;
    }
  else{
    return false;
    }
}
void requestEvent()
{
  Wire.write(ravijn); 
  Wire.write(obstacel); 
  Wire.write(correctieLinks); 
  Wire.write(correctieRechts);       
  Wire.write(stoppen);              
  }
