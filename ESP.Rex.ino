#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>

MDNSResponder mdns;
 
ESP8266WebServer server(80);
  String webPage;
  const char* ssid     = "Tesla IoT";      //wifi "Tesla IoT" Theo
  const char* password = "fsL6HgjN";  //wifi password "fsL6HgjN" qwertyuiopasd

  int forwardPin[] = /*{16,2,14,13}*/{0,0,12,15};
  int reversePin[] = /*{0,0,12,15}*/{16,2,14,13};

  bool ravijn;
  bool obstacel;  
  bool irSensorLinkerkant;  
  bool irSensorRechterkant;
  bool bocht;
  bool stoppen;
  bool automatisch = false;

void setup() {
  
  Wire.begin(); 
  
  pinMode(forwardPin[0], OUTPUT); 
  pinMode(reversePin[0], OUTPUT);

  pinMode(forwardPin[1], OUTPUT); 
  pinMode(reversePin[1], OUTPUT); 

  pinMode(forwardPin[2], OUTPUT); 
  pinMode(reversePin[2], OUTPUT); 

  pinMode(forwardPin[3], OUTPUT); 
  pinMode(reversePin[3], OUTPUT); 


 
  webPage += "<h1>Rex The Car</h1><p>";
  webPage += "<a href=\"forwardButton\"><button>Rechtdoor</button></a>&nbsp;";
  webPage += "<a href=\"reverseButton\"><button>Achteruit</button></a>&nbsp;";
  webPage += "<a href=\"leftButton\"><button>Links</button></a>&nbsp;";
  webPage += "<a href=\"rightButton\"><button>Rechts</button></a>&nbsp;";
  webPage += "<a href=\"stopButton\"><button>Stoppen</button></a>&nbsp";
  webPage += "<a href=\"automaticOnButton\"><button>Autonoom aan</button></a>&nbsp";
  webPage += "<a href=\"automaticOffButton\"><button>Autonoom uit</button></a></p>;";

  
  Serial.begin(74880);
  delay(100);
 
 
  Serial.println();
  Serial.println();
  Serial.print("Verbinding maken met ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi aangesloten");  
  Serial.println("IP addres: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) 
    Serial.println("MDNS responder gestart");
 
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/forwardButton", [](){
    server.send(200, "text/html", webPage);         //forward button
    Vooruit();
  });
  
  server.on("/reverseButton", [](){
    server.send(200, "text/html", webPage);         //reverse button
    Achteruit();
  });
  
   server.on("/stopButton", [](){
    server.send(200, "text/html", webPage);         //stop button
    Stoppen();
  });
  server.on("/leftButton", [](){
    server.send(200, "text/html", webPage);         //links button
    Links();
  });
  server.on("/rightButton", [](){
    server.send(200, "text/html", webPage);         //rechts button
    Rechts();
  });
  
  server.on("/automaticOnButton", [](){
    server.send(200, "text/html", webPage);         //rechts button

    automatisch = true;

  });
  server.on("/automaticOffButton", [](){
    server.send(200, "text/html", webPage);         //rechts button

    automatisch = false;
    Stoppen();

  });
  
  server.begin();
  Serial.println("HTTP server gestart");
}
 
void loop() {
  server.handleClient();
  
  Wire.requestFrom(9,5);
  //while(Wire.available())    // slave may send less than requested
 //{
  ravijn = Wire.read();
  obstacel = Wire.read();  
  irSensorRechterkant = Wire.read();  
  irSensorLinkerkant = Wire.read();
  stoppen = Wire.read();

 /*
    Serial.print("ravijn: ");
    Serial.println(ravijn);
    Serial.print("Obstakel: ");
    Serial.println(obstacel);
    Serial.print("irSensorLinkerkant: ");
    Serial.println(irSensorLinkerkant);
    Serial.print("irSensorRechterkant: ");
    Serial.println(irSensorRechterkant);
  */
  if(automatisch == true)
  {
   /*if(ravijn == true){
    delay(100);
      if(ravijn == true){
            Achteruit(); // achteruit en keren
            delay(1000);
            Links();
            delay(5100);
      }
    }
   */
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   if(irSensorLinkerkant == false && irSensorLinkerkant == false){
   Achteruit(); 
   delay(2000);
   
   if(irSensorLinkerkant == false && irSensorRechterkant == true ){
    Links();
    delay(1000);
   }else if(irSensorLinkerkant == true && irSensorRechterkant == false ){
    Rechts();
    delay(1000);
   }
   
   } 
   /*
   else if(irSensorLinkerkant == false){
    Achteruit(); //Moet naar rechts 
    delay(700);
    Rechts();
    delay(1200);
   }
   
   else if(irSensorRechterkant == false){
    Achteruit();// Moet naar links
    delay(700);
    Links();
    delay(1200);
   }
   */
   //else if(obstacel == false){
    //Rechts(); /* Net zolang naar links draaien totdat obstacel 0 is */
   //}  
   else if(stoppen == true){
    Stoppen();    /* Persoon gedetecteerd, STOPPEN!*/
    delay(2000);
   }
   else{
    Vooruit();
    } 
   }
}




void Vooruit()
  {
        
  digitalWrite(forwardPin[0], HIGH); 
  digitalWrite(reversePin[0], LOW);

  digitalWrite(forwardPin[1], HIGH); 
  digitalWrite(reversePin[1], LOW);

  digitalWrite(forwardPin[2], HIGH); 
  digitalWrite(reversePin[2], LOW);

  digitalWrite(forwardPin[3], HIGH); 
  digitalWrite(reversePin[3], LOW);
  }
  
void Achteruit()
  {       
  digitalWrite(forwardPin[0], LOW); 
  digitalWrite(reversePin[0], HIGH);

  digitalWrite(forwardPin[1], LOW); 
  digitalWrite(reversePin[1], HIGH);

  digitalWrite(forwardPin[2], LOW); 
  digitalWrite(reversePin[2], HIGH);
  
  digitalWrite(forwardPin[3], LOW); 
  digitalWrite(reversePin[3], HIGH);
  }
void Stoppen()
  {
  digitalWrite(forwardPin[0], LOW); 
  digitalWrite(reversePin[0], LOW);

  digitalWrite(forwardPin[1], LOW); 
  digitalWrite(reversePin[1], LOW);

  digitalWrite(forwardPin[2], LOW); 
  digitalWrite(reversePin[2], LOW);

  digitalWrite(forwardPin[3], LOW); 
  digitalWrite(reversePin[3], LOW);
  }
void Rechts()
  {
  digitalWrite(forwardPin[0], HIGH); 
  digitalWrite(reversePin[0], LOW);

  digitalWrite(forwardPin[1], HIGH); 
  digitalWrite(reversePin[1], LOW);

  digitalWrite(forwardPin[2], LOW); 
  digitalWrite(reversePin[2], HIGH);

  digitalWrite(forwardPin[3], LOW); 
  digitalWrite(reversePin[3], HIGH);
  }
void Links()
  {     
  digitalWrite(forwardPin[0], LOW); 
  digitalWrite(reversePin[0], HIGH);

  digitalWrite(forwardPin[1], LOW); 
  digitalWrite(reversePin[1], HIGH);

  digitalWrite(forwardPin[2], HIGH); 
  digitalWrite(reversePin[2], LOW);

  digitalWrite(forwardPin[3], HIGH); 
  digitalWrite(reversePin[3], LOW);
  }
