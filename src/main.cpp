#include <Arduino.h>
#include <ESPAsyncWebServer.h>


/**
 *The file manager of eps32 // That allows us to upload the html file in eps32 
*/
#include <SPIFFS.h>

/**
 * the conf for to connect on the WiFI
 */

const char* ssid ="nom-wifi";
const char* password ="mot-de-pass-du-wifi";

const int led = 2;
const int aspirateurPin = 20;

const int etatVanne = 34;

AsyncWebServer server(80);

void setup() {
 /***************************Serial******************/
 Serial.begin(115200);
 while (!Serial){}
 Serial.println("\n");


/***************************GPIO******************/

pinMode(led, OUTPUT);
digitalWrite(led,LOW);
pinMode(aspirateurPin,OUTPUT);
 
/********************SPIFFS********************/
    if(!SPIFFS.begin()){
      Serial.println("Erreur SPIFFS");
      return;
    }
 /*****************Optinal **********************/
 /*Opening of the root of the file system*/
 File root = SPIFFS.open("/");
 /*Geting of the fisrt file in this file system*/
 File file = root.openNextFile();
  /*Loop for get all the file */
 while (file)
 {
   Serial.print("File: ");
   Serial.println(file.name());
   file.close();
   file = root.openNextFile();

 }
 /**************Wifi**************************/
WiFi.begin(ssid,password);
Serial.println("Trying to connect");


while (WiFi.status() != WL_CONNECTED)
{
 Serial.println(".");
 delay(100);
}

Serial.println("\n");
Serial.println("Connection established");
Serial.println("Adresse IP : ");
Serial.println(WiFi.localIP());

/******************Server******************/
/**
 *If we tap the link 'Adresse IP' of the eps on the browser of my cellphone wich is already connected on the same  wifi, i get the page index.html  
*/
server.on("/",HTTP_GET,[](AsyncWebServerRequest * request){
  request->send(SPIFFS, "/index.html", "text/html");
});

server.on("/w3.css",HTTP_GET,[](AsyncWebServerRequest * request){
  request->send(SPIFFS, "/w3.css", "text/css");
});


server.on("/script.js",HTTP_GET,[](AsyncWebServerRequest * request){
  request->send(SPIFFS, "/script.js", "text/javascript");
});


server.on("/lireEtat",HTTP_GET,[](AsyncWebServerRequest * request){
 int val = analogRead(aspirateurPin);
  
  String etat = String(val);
  request->send(200, "text/plain",etat);
});


server.on("/on",HTTP_GET,[](AsyncWebServerRequest * request){
  digitalWrite(aspirateurPin,HIGH);
  digitalWrite(led,HIGH);
  
  request->send(200);
});

server.on("/off",HTTP_GET,[](AsyncWebServerRequest * request){
  digitalWrite(led,LOW);
  
  digitalWrite(aspirateurPin,LOW);
  request->send(200);
});

server.begin();

Serial.println("Server online");


 }

void loop() {


/**
 * 
 *
*/ 


}