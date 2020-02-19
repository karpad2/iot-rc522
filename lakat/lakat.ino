/*
 * 
 *by Kovács Árpád
 * 
 */
#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
//#include <HTTPClient.h>
#define SS_PIN    21
#define RST_PIN   22
#define SIZE_BUFFER     18
#define MAX_SIZE_BLOCK  16
#define device 1
#define ledpin 14
const char* card = "AB 6F C7 1B"; 
const char* host = "192.168.0.31";
const char* ssid     = "halozatunk-koz";
const char* password = "12345Koz67890";
bool locked=true;

void web_service(int _status=0)
{

   
   Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url ="/lock/lock.php?status";
    

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
		if(line=="locked")
			locked=true;
		else if(line=="unlocked") locked=0;
		else {}
    }

    Serial.println();
    Serial.println("closing connection");
}
     
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  pinMode(ledpin,OUTPUT);
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
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());


}
void loop() 
{
	web_service();
	if(locked)
	digitalWrite(ledpin,HIGH);
	else digitalWrite(ledpin,LOW);
delay(1500);	
}
