#include "WiFi.h"
#include <WebServer.h>
//輸入你的SSID/password
char* wifi_ssid = "dawn";
char* wifi_password = "00000000";
int statusCode;
String room_id = "";
String valString = "";
String valbuffer = "";
int valcount = 0;


//宣告webserver
WebServer server(80);
void setup() {
  Serial.begin(9600);
  WiFi.begin(wifi_ssid, wifi_password);
  if (testWifi()) {
    Serial.println("WiFi connected OK");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
    //設定webserver0
    server.begin();
    Serial.println("Server started");
  }
  else {
    Serial.println("WiFi connected NG");
  }

  pinMode(41, INPUT); // Setup for leads off detection LO +
  pinMode(40, INPUT); // Setup for leads off detection LO -

  server.on("/test", []() {

    int lastIndex = valbuffer.length() - 1;
    valbuffer.remove(lastIndex);

    //String content = "{\"val\":" + valString + "}";
    String content1 = "{\"val\":[" + valbuffer + "]}";
    server.enableCORS();
    server.send(200, "application/json", content1);
    valbuffer = "";
    content1 = ""; 
    valcount = 0;
  });
  server.on("/init", []() {
    valbuffer = "";
    server.enableCORS();
    server.send(200);
  });
}

void loop() {
  //handleClient要放在loop
  server.handleClient();
  if ((digitalRead(40) == 1) || (digitalRead(41) == 1)) {
    Serial.println(digitalRead(10));
    Serial.println(digitalRead(11));
    sendData(4095);
  }
  else{
    const int _val = analogRead(A0);
    Serial.println(_val);
    sendData(analogRead(A0));
  }
}

bool testWifi(void) {
  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) {
      return true;
    }
    delay(500);
    Serial.print(WiFi.status());
    c++;
  }
  return false;
}

void sendData(int val) {
  valString = String(val);
  if(valcount < 2000){
    valbuffer += String(valString)+",";  
    valcount++;
  }

}
