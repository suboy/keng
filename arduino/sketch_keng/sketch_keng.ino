#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const String ssid = "Tencent-StaffWiFi";  // 需要连接的wifi热点名称
const String password = "";               // 需要连接的wifi热点密码
const String token = "67tw2f35Hye9N7sx";
int wifiConnected = 0;

const int doorPin1 = 12;
const int doorPin2 = 13;
const int doorPin3 = 14;
const int doorPin4 = 15;

int doorState1 = 0;
int doorState2 = 0;
int doorState3 = 0;
int doorState4 = 0;
int doorState = 10000;
int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state = 0;
char stateStr[5];

void setup() {
  Serial.begin ( 9600 );
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(doorPin1, INPUT);
  pinMode(doorPin2, INPUT);
  pinMode(doorPin3, INPUT);
  pinMode(doorPin4, INPUT);
  connectWifi();
}

void loop() {
  state1 = digitalRead(doorPin1);
  state2 = digitalRead(doorPin2);
  state3 = digitalRead(doorPin3);
  state4 = digitalRead(doorPin4);
  state = state1 + state2*10 + state3*100 + state4*1000 + 10000;
  Serial.println(stateStr);
  if(state != doorState && wifiConnected == 1){
    doorState = state;
    itoa(state, stateStr, 10);
    uploadData(stateStr);
  }
  delay(1000);
}

void connectWifi() {
  int connectCount = 0;
  byte mac[6];
  WiFi.begin ( ssid.c_str(), password.c_str() );
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[0],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.println(mac[5],HEX);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 1000 );
    Serial.print ( "." );
    if(connectCount > 30) {
      Serial.println( "Connect fail!" );
      break;
    }
    connectCount += 1;
  }
  if(WiFi.status() == WL_CONNECTED) {
    Serial.println ( "" );
    Serial.print ( "Connected to " );
    Serial.println ( ssid );
    Serial.print ( "IP address: " );
    Serial.println ( WiFi.localIP() );
    connectCount = 0;
    wifiConnected = 1;
  }
}

void uploadData(String data) {
  HTTPClient http;
  const String url = "/keng/update/" + token + "/" + data;
  Serial.println(url);
  http.begin("suboy.cn", 80, url);
//  http.addHeader("U-ApiKey",UKey, true);
//  int httpCode =  http.POST("{\"value\":" + data + "}");
  int httpCode =  http.GET();                  // 使用GET形式来取得数据
  Serial.print("code:");
  Serial.println(httpCode);
  if(httpCode == 200) {                       // 访问成功，取得返回参数
      String payload = http.getString();
      Serial.println(payload);
  } else {                                    // 访问不成功，打印原因
     String payload = http.getString();
     Serial.print("context:");
     Serial.println(payload);
  }
}
