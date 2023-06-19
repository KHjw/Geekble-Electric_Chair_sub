 /*
 *
 * @file Geekble Electric Chair_sub.ino
 * @author 홍진우 (kevinlike@naver.com)
 * @brief
 * @version 1.0
 * @date 2023-06-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ElectricChair_sub.h"

void setup(){
  Serial.begin(115200);
  Serial.println("===============TTGO INIT===============");
  Serial_HandShake();
  // TimerInit();
  // NeopixelInit();
  // LedInit();
  // LightControl(RED, STATIC, STATIC, STATIC);
  // EsInit();
  Serial.println("===============TTGO INITALIZED===============");
}

void loop(){
  Serial_RestartCheck();
  // ShockTimer.run();
  // BlinkTimer.run();
  // BreatheTimer.run();
  delay(1000);
}