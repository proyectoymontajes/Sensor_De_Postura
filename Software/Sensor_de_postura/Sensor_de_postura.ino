#include <WiFi.h>
const int sensorPin= 35;

const char*ssid     = "ssid";
const char*password = "password";
const int vibra = 33;
const int sensor= 34;



int sensorVal =0;

WiFiServer server(80);

void setup()
{
    Serial.begin(9600);   
    pinMode(vibra, OUTPUT);   
    pinMode(sensor, INPUT); 
    
    delay(10);


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
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
  
  int val = analogRead(sensorPin);
  float millivolts = (val / 1023.0) * 101.5;
  float celsius = millivolts / 10; 
  Serial.print(celsius);
  Serial.println(" C");
  delay(1000);

sensorVal=digitalRead(sensor);
 
 if(sensorVal == HIGH){

  digitalWrite(vibra, HIGH);
  delay(1);
 }
else
 {
  digitalWrite(vibra, LOW);
  delay(1);
 }


 WiFiClient client = server.available();   

  if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected()) {           
      if (client.available()) {            
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    

       
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<!DOCTYPE html>");
            client.print("<html>");
            client.print("<head><title>ola :v</title><meta http-equiv='refresh' content='1'></head>");
            client.print("<body style='background-color: rgb(20,21, 38);'>");
            client.print("<h1 style='font-size: 50px;top:100px;color: white;position: relative;text-align: center; font-family: Arial, Helvetica, sans-serif;'>Sensor de Postura</h1>");
            client.print("<h1 style='z-index: 1; top:380px;color: white;position: relative;text-align: center; font-family: Arial, Helvetica, sans-serif;'>Temperatura</h1>");
            client.print("<h1 style='z-index: 1; top: 240px;color: white;position: relative;text-align: center; font-family: Arial, Helvetica, sans-serif;'>"+String(celsius)+"</h1>");
            client.print("<div class='SensorTemp' style=' position: relative; top: 100px; height: 200px;width: 200px; background-color: rgb(33, 37, 44);margin: auto;border-radius: 50%; overflow: hidden;'>");
            client.print("<div class='barraTemp'style='transform:rotate("+String(map(celsius,0,100,0,180))+"deg);'>");
            client.print("<div class='bar' style= 'background-color: white;height: 100px; width: 200px;'></div>");
            client.print("<div class='conteiner' style=' background-color: rgb(172, 47, 235);height: 100px;width: 200px;'></div>");
            client.print("</div>");
            client.print("<div class='circulo' style='position: relative; height:150px ; width:150px ; background-color: rgb(20,21, 38); margin: auto;border-radius: 50%; position: relative; margin: -175px auto;'></div>");
            client.print("<div class='rectangulo' style='top: 100px; position: relative;margin: auto; width: 300px; height: 200px; background-color: rgb(20,21, 38);'></div>"); 
            client.print("</div>");
            client.print("<div class='post'style='background-color: transparent; margin: auto; 200px;width: 200px;position: relative;top: 400px;'>");
            client.print("<div class='pared' style='position: relative;background-color: azure;height: 200px;width: 10px;'></div>");
            client.print("<div class='pared2' style='position: relative;background-color: azure;height: 10px;width: 200px;'></div>");
            client.print("</div>");
            client.print("<div class='circu' style='left:200px;background-color: transparent;width: 410px;height: 400px;position: relative;top: 190px;z-index: -1;border-radius: 50%;transform: rotate("+String(map(sensorVal,0,10,0,730))+"deg);'>");
            client.print("<div class='cir' style='background-color: blueviolet;height: 30px;width: 30px;border-radius: 50%;left: 220px;position: relative;'></div>");
            client.print("</div>");
            client.print("<h1 class='incli' style='color: white;text-align: center;font-family: Arial, Helvetica, sans-serif;'>Inclinacion</h1>");
            client.print("");
            client.print("");
            client.println();
            client.print("</body>");
            client.print("</html>");
           

            break;
          } else {    
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }

      }
    }
    
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
 