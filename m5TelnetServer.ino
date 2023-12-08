#include "WifiConfig.h"
#include <stdarg.h>
#include <WiFi.h>
#include <M5Unified.h> 

const int port = 23;

WiFiServer server(port);

// グローバル変数（プログラム全体で使用する変数の定義をします。）
uint32_t count;

void printBoth(bool ln,const char* format, ...) {
  va_list args;
  va_start(args, format);

  // フォーマットされた文字列を格納するためのバッファを作成
  char buffer[256]; // 適切なサイズを設定してください
  vsnprintf(buffer, sizeof(buffer), format, args);

  if(ln) println(buffer);
  else print(buffer);

  va_end(args);
}

void println(const char* str) {
  Serial.println(str);         // シリアルモニターにHello World!!と1行表示
  M5.Display.println(str);       // 画面に1行表示
}

void print(const char* str){
  Serial.print(str);         // シリアルモニターにHello World!!と1行表示
  M5.Display.print(str);       // 画面に1行表示
}

String ipToString(IPAddress ip) {
  return String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
}

void setup()
{
  auto cfg = M5.config();       // M5Stack初期設定用の構造体を代入

  M5.begin(cfg);                // M5デバイスの初期化
  printBoth(true,"Telnet Server");
  count = 0;                               // countを初期化
  printBoth(true,"Cnect to:");
  printBoth(true,ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      printBoth(false,".");
  }

  printBoth(true,"");
  printBoth(true,"WiFi Cnected.");
  printBoth(true,"IP address: ");
  String ipAddress = ipToString(WiFi.localIP());
  printBoth(true, "%s", ipAddress.c_str());
  printBoth(false,"Svr port: ");
  printBoth(true,"%d",port);
  printBoth(true,"=====");

  server.begin();
}


void loop(){
 WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    printBoth(true,"New Client.");

    while (client.connected()) {
      
      printBoth(false,"+");
      client.write("+");

      delay(1000);
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
}