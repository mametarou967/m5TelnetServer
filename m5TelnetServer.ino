#include "WifiConfig.h"
#include <stdarg.h>
#include <WiFi.h>
#include <M5Unified.h> 

const int port = 23;

WiFiServer server(port);

// グローバル変数（プログラム全体で使用する変数の定義をします。）
uint32_t count;

void setTextSize()
{
  int textSize = 2;
  switch (M5.getBoard()) {
    case m5::board_t::board_M5Stack:
      textSize = 3;
      break;
    default:
      break;
  }
}

void printBoth(const char* format, ...) {
  va_list args;
  va_start(args, format);

  // フォーマットされた文字列を格納するためのバッファを作成
  char buffer[256]; // 適切なサイズを設定してください
  vsnprintf(buffer, sizeof(buffer), format, args);

  // シリアルポートに出力
  Serial.println(buffer);

  // M5Stackのディスプレイに出力
  M5.Display.println(buffer);

  va_end(args);
}

void println(const char* str) {
  Serial.println(str);         // シリアルモニターにHello World!!と1行表示
  M5.Display.print(str);       // 画面に1行表示
}

void setup()
{
  auto cfg = M5.config();       // M5Stack初期設定用の構造体を代入

  M5.begin(cfg);                // M5デバイスの初期化
  setTextSize();
  printBoth("Hello World!!");
  count = 0;                               // countを初期化
    /*
    Serial.begin(115200);

    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Server port: ");
    Serial.println(port);

    server.begin();
    */
}


void loop(){
  M5.Display.setCursor(0, 20);              // 文字の描画座標（カーソル位置）を設定
  printBoth("COUNT: %d\n", count);
  count++;                                  // countを1増やす
  delay(1000);                              // 1秒待つ
  /*
 WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");

    while (client.connected()) {
      //if (client.available()) {
        // char c = client.read();
      //}
      Serial.write("Hello Client!");
      client.write("Hello Client!");

      delay(1000);
    }

    client.stop();
    Serial.println("Client Disconnected.");
  }
  */
}