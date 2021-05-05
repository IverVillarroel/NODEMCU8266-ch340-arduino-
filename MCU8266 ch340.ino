#include <DHT.h>     //libreria sensor de temperatura y humedad
#include <DHT_U.h>
#include <ESP8266WiFi.h> //libreria integrado wifi

#define D1 5   //entrada de la señal
DHT dht(D1, DHT11);

String ssid = "Tigo Flia Villarroel"; //nombre de la red
String password = "25291711";         //password de la red
WiFiServer server(80); //objeto de la clase WiFiServer

float temp, hume;

void setup(){
  Serial.begin(9600);   //puerto serial
  dht.begin();
 // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED ) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("********************************************");
  Serial.print("Conectado a la red WiFi: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("macAdress: ");
  Serial.println(WiFi.macAddress());
  Serial.println("*********************************************");
  
  server.begin(); //begin() levantamos el servidor   
 }
void loop(){
  hume = dht.readHumidity();
  temp = dht.readTemperature();
  delay(10000);

  Serial.println("Temperatura: " + String(temp) + " Humedad: " + String (hume));
  delay(10000);

   
  WiFiClient client = server.available(); //objeto de la clase WiFiClient
  // avalaible() detecta un cliente nuevo del objeto de la clase WifiServer
  if(!client){
    return;
  }
  
  Serial.println("Nuevo cliente...");
  while(!client.available()){ //espera a un cliente diponible
    delay(1);
  }

  String peticion = client.readStringUntil('\r'); //lee la peticion del cliente
  Serial.println(peticion);
  client.flush(); //limpia la peticion del cliente

  //client.println("HTTP/1.1 200 OK");
  client.println("");
  client.println("");
  client.println("");
  client.println(""); 

//inicio de la pagina
//codigo HTML
  client.println("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>TEMPERATURA Y HUMEDAD</title></head><body style='font-family: Century gothic; width: 800;'><center><div style='box-shadow: 0px 0px 20px 8px rgba(0,0,0,0.22); padding: 20px; width: 300px; display: inline-block; margin: 30px;'> <h2>TEMPERATURA=" +String (temp) + "°C</h2><h2>HUMEDAD =" +String (hume) + "%</h2></div></center></body></html>");

//fin de la pagina 

  delay(10);
  Serial.println("Peticion finalizada");
  Serial.println("");  
}
