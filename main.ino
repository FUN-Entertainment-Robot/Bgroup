#include <M5Stack.h>

int led1 = 16;
int led2 = 17;
int led3 = 1;  // 追加したピン番号
// PWMの設定
const double PWM_Hz = 50;
const uint8_t PWM_level = 16;
void setup() {
  Serial.begin(115200);
  m5.begin();
  pinMode(led1, OUTPUT);　//右腕
  pinMode(led2, OUTPUT);  //左腕
  pinMode(led3, OUTPUT);  // 頭、追加したピンを出力モードに設定
  ledcSetup(1, PWM_Hz, PWM_level);
  ledcSetup(2, PWM_Hz, PWM_level);
  ledcSetup(3, PWM_Hz, PWM_level);  // 追加したピンのPWMチャンネルと周波数を設定
  //モータのピンとチャンネルの設定
  ledcAttachPin(led1, 1);
  ledcAttachPin(led2, 2);
  ledcAttachPin(led3, 3);
}
void loop() {
  M5.update();
  if (M5.BtnA.wasReleased()) {  //Aボタンを押したとき頭を三回振る
    for (int k = 0; k <= 2; k++) {
      for (int x = 3613; x > 2613; x -= 100) {
        ledcWrite(3, x);  // led3に対してPWM信号を出力
        delay(100);
        Serial.printf("%d\n", x);
      }
      for (int x = 2613; x <= 3613; x += 100) {
        ledcWrite(3, x);  // led3に対してPWM信号を出力
        delay(100);
        Serial.printf("%d\n", x);
      }
    }
  }
  if (M5.BtnB.wasReleased()) {  //Bボタンを押したときうなだれる
    for (int x = 3613; x > 2613; x -= 30) {
      ledcWrite(3, x);  // led1に対してPWM信号を出力
      delay(100);
      Serial.printf("%d\n", x);
    }
    for (int x = 2613; x <= 3613; x += 100) {
      ledcWrite(3, x);  // led3に対してPWM信号を出力
      delay(100);
      Serial.printf("%d\n", x);
    }
  }
}
if (M5.BtnC.wasReleased()) {  //Cボタンを押したとき三回両腕を振る
  for (int k = 0; k <= 2; k++) {
    for (int i = 3500, j = 5000; i <= 5000 && j > 3500; i += 100, j -= 100) {  //-90度(0.5ms)は1638,90度(2.4ms)は7864,0度は3113
      ledcWrite(1, i);                                                         // led1に対してPWM信号を出力
      ledcWrite(2, j);                                                         // led2に対してPWM信号を出力
      delay(60);
      Serial.printf("%d\n", i);
    }
    for (int i = 5000, j = 3500; i > 3500 && j <= 5000; i -= 100, j += 100) {
      ledcWrite(1, i);  // led1に対してPWM信号を出力
      ledcWrite(2, j);  // led2に対してPWM信号を出力
      delay(60);
      Serial.printf("%d\n", i);
    }
  }
