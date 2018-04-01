#include <ESP8266HTTPClient.h>
#include "http.h"

const String token = "67tw2f35Hye9N7sx";


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