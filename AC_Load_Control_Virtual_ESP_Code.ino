#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

const char* ssid = "Rafi";
const char* password = "qnh1013hg";
String cmd; bool state1; bool state2; 

WebSocketsServer webSocket = WebSocketsServer(81);

#define LED1  2  // GPIO pin where the LED is connected
#define LED2  4 

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  if(type == WStype_TEXT) {

   
     cmd = String((char*)payload);
      //cmd = data.charAt(0);
      Serial.print("Received data: ");
      Serial.println(cmd[0]);
  }

}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(LED1,OUTPUT); 
  pinMode(LED2,OUTPUT); 

  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  
   webSocket.loop();

   if (cmd[0] == '1')
    {
      state1 = !state1; 
      digitalWrite(LED1, state1); 
      cmd[0]= '0'; 
      
      }
   if (cmd[0] == '2')
    {
      state2 = !state2; 
      digitalWrite(LED2, state2); 
      cmd[0]= '0'; 
      
      }
   
}
