#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "wifi.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "cn.ntp.org.cn", 8*3600, 60000);

const String ssid = "Tencent-StaffWiFi";  // 需要连接的wifi热点名称
const String password = "";               // 需要连接的wifi热点密码
int wifiConnected = 0;

int wifiIsConnected(){
    return wifiConnected;
}

void connectWifi() {
  int connectCount = 0;
  byte mac[6];
  WiFi.begin ( ssid.c_str(), password.c_str() );
  WiFi.macAddress(mac);
  Serial.println("MAC: ");
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
    timeClient.update();
    timeClient.begin();
    Serial.println(timeClient.getFormattedTime());
  }
}

String getTime(){
    return timeClient.getFormattedTime();
}