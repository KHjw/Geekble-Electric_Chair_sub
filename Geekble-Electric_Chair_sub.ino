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
  TimerInit();
  NeopixelInit();
  // WifiInit();
  EsInit();
  DfpInit();
  Serial_HandShake();
  Serial.println("===============TTGO INITALIZED===============");
}

// 흰색 - Neo / 보라 - SerialRecv "ok" / 노랑 - DFP / 빨강 - wifi / 

void loop(){
  Serial_Read();
  ShockTimer.run();
  BlinkTimer.run();
  BreatheTimer.run();
  RiseTimer.run();
  EffectTimer.run();
}