#include <Arduino.h>
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
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

#line 15 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
void setup();
#line 25 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
void loop();
#line 2 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void EsInit();
#line 6 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Stage(int stage);
#line 29 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Control(int start_point, int end_point);
#line 36 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Loop_Confirm(int loop_num);
#line 41 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Start();
#line 2 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void NeopixelInit();
#line 9 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void AllNeoColor(int color_code);
#line 15 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void NeoBlink(int neo_code, int color_code);
#line 33 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void LedInit();
#line 40 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void LedColor(int color_code);
#line 81 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void LedBlink(int color_code);
#line 91 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void LightControl(int color_code, int led_mode, int tag_mode, int bot_mode);
#line 110 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void LightMode(int light_code, int color_code, int mode);
#line 2 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void SerialInit();
#line 5 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void Serial_HandShake();
#line 24 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void Serial_RestartCheck();
#line 33 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void Serial_Read();
#line 59 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void Serial_Send(String data);
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void TimerInit();
#line 12 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BlinkTimerStart(int Neo, int NeoColor);
#line 20 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BlinkTimerFunc();
#line 32 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BlinkLedtagTimerFunc();
#line 47 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BlinkAllTimerFunc();
#line 66 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BreatheTimerStart(int Neo, int NeoColor);
#line 72 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BreatheTimerFunc();
#line 83 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void ShockTimerFunc();
#line 88 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void ConnTimerFunc();
#line 15 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
void setup(){
  Serial.begin(115200);
  Serial_HandShake();
  SerialInit();
  TimerInit();
  NeopixelInit();
  LedInit();
  LightControl(RED, BLINK, BLINK, BREATHE);
}

void loop(){
  Serial_Read();
  ShockTimer.run();
  BlinkTimer.run();
  BreatheTimer.run();
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
//****************************************ES SETUP****************************************
void EsInit(){
  pinMode(ES_PIN, OUTPUT);
}
//****************************************ES Stage****************************************
void ES_Stage(int stage){
  switch (stage){
  case 1:
    ES_Control(1,3);
    ES_Control(4,8);
    ES_Loop_Confirm(2);
    break;
  case 2:
    ES_Control(1,3);
    ES_Control(4,8);
    ES_Loop_Confirm(4);
    break;
  case 3:
    ES_Control(1,2);
    ES_Control(3,5);
    ES_Loop_Confirm(4);
    break;
  case 0:
  default:
    break;
  }
}

void ES_Control(int start_point, int end_point){
  EsArr[EsArr_cnt] = start_point;
  EsArr_cnt ++;
  EsArr[EsArr_cnt] = end_point;
  EsArr_cnt ++;
}

void ES_Loop_Confirm(int loop_num){
  EsArr_cnt = 0;
  shock_cnt = 0;
}

void ES_Start(){
  EsArr;
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
//****************************************Neopixel SETUP****************************************
void NeopixelInit(){
  Serial.println("NeopixelInit");
  for(int i=0; i<NeoNum; i++){
    pixels[i].begin();
  }
}

void AllNeoColor(int color_code){
  for(int n=0; n<NeoNum; n++){
    pixels[n].lightColor(color[color_code]);
  }
}

void NeoBlink(int neo_code, int color_code){
  for(int n=0; n<blink_num; n++){
    if(neo_code == ALLNEO){
      AllNeoColor(BLACK);
      delay(blink_time);
      AllNeoColor(color_code);
      delay(blink_time);
    }
    else{
      pixels[neo_code].lightColor(color[BLACK]);
      delay(blink_time);
      pixels[neo_code].lightColor(color[color_code]);
      delay(blink_time);
    }
  }
}

//****************************************Led SETUP****************************************
void LedInit(){
  Serial.println("LedInit");
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void LedColor(int color_code){
  switch(color_code){
    case RED:
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
      break;
    case GREEN:
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
      break;
    case BLUE:
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, HIGH);
      break;
    case YELLOW:
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, LOW);
      break;
    case PURPLE:
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, HIGH);
      break;
    case WHITE:
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_B, HIGH);
      break;
    case BLACK:
    default:
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
      break;
  }
}

void LedBlink(int color_code){
  for(int n=0; n<blink_num; n++){
    LedColor(BLACK);
    delay(blink_time);
    LedColor(color_code);
    delay(blink_time);
  }
}

//****************************************Light Control****************************************
void LightControl(int color_code, int led_mode, int tag_mode, int bot_mode){
  int sum = led_mode + tag_mode + bot_mode;

  LightMode(LED, color_code, led_mode);
  if(sum < BLINK*2){
    LightMode(TAG, color_code, tag_mode);
    LightMode(BOT, color_code, bot_mode);
  }
  else if(sum >= BLINK*2){
    BlinkTimer.deleteTimer(BlinkTimerId);
    BlinkTimerStart(LEDTAG, color_code);
    LightMode(BOT, color_code, bot_mode);
  }
  else if(sum >= BLINK*3){
    BlinkTimer.deleteTimer(BlinkTimerId);
    BlinkTimerStart(ALLNEO, color_code);
  }
}

void LightMode(int light_code, int color_code, int mode){
  if(light_code == LED){
    Serial.print("LED Mode : ");
    switch(mode){
      case STATIC:
        LedColor(color_code);
        Serial.print("static");
        break;
      case BLINK:
        LedBlink(color_code);
        Serial.print("blink");
        break;
      case BREATHE: // LED는 숨쉬기 모드가 없다
      default:
        LedColor(BLACK);
        Serial.print("off");
        break;
    }
  }
  else{
    Serial.print(" NEO Mode : ");
    switch(mode){
      case STATIC:
        pixels[light_code].lightColor(color[color_code]);
        Serial.print("static");
        break;
      case BLINK:
        Serial.print("blink");
        BlinkTimer.deleteTimer(BlinkTimerId);
        BlinkTimerStart(light_code, color_code);
        break;
      case BREATHE:
        Serial.print("breathe");
        BreatheTimer.deleteTimer(BreatheTimerId);
        BreatheTimerStart(light_code, color_code);
        break;
      default:
        Serial.print("off");
        pixels[light_code].lightColor(color[BLACK]);
        break;
    }
  }
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
//****************************************Serial Communication****************************************
void SerialInit(){
}

void Serial_HandShake(){
  subTTGO.begin(9600, SERIAL_8N1, SUBTTGO_RX_PIN, SUBTTGO_TX_PIN);
  RECONNECT_TTGO:
  Serial.println("Connecting to TTGO");
  subTTGO.println("connect");
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil('\n');
    if(recv_data == "connect"){
      subTTGO.println("ok");
      goto RECONNECT_TTGO;
    }
    else if(recv_data == "ok"){
      Serial.println("TTGO CONNECTED");
    }
    else
      goto RECONNECT_TTGO;
  }
}

void Serial_RestartCheck(){
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil('\n');
    if(recv_data == "connect"){
      subTTGO.println("ok");
    }
  }
}

void Serial_Read(){
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil('\n');
    if(recv_data == "connect")             {subTTGO.println("ok");
                                            LightControl(PURPLE, STATIC, STATIC, STATIC);}
    else if(recv_data == "setting")         LightControl(WHITE,  STATIC, STATIC, STATIC);
    else if(recv_data == "ready")       		LightControl(RED,    STATIC, STATIC, BREATHE);
    else if(recv_data == "activate_wait")   LightControl(YELLOW, STATIC, STATIC, BREATHE);
    else if(recv_data == "activate_t1")		  LightControl(GREEN,  STATIC, STATIC, BREATHE);
    else if(recv_data == "activate_t2") 		LightControl(GREEN,  BLINK,  BLINK,  BREATHE);
    else if(recv_data == "activate_t3") 		LightControl(BLUE,	 STATIC, STATIC, BREATHE);
    else if(recv_data == "stage1")     		 {LightControl(BLUE,   STATIC, STATIC, BREATHE);
                                            ES_Stage(1);}
    else if(recv_data == "stage2")     		 {LightControl(BLUE,   STATIC, STATIC, BREATHE);
                                            ES_Stage(2);}
    else if(recv_data == "stage3")				 {LightControl(BLUE,   STATIC, STATIC, BREATHE);
                                            ES_Stage(3);}
    else if(recv_data == "cool")						LightControl(RED,    STATIC, STATIC, BREATHE);
    else if(recv_data == "rescue")					LightControl(GREEN,  STATIC, BLINK,  RISE);
    else if(recv_data == "rescue_suc")			LightControl(GREEN,  STATIC, STATIC, STATIC);
    else if(recv_data == "rescue_fail")		  LightControl(RED,    BLINK,  BLINK,  BLINK);
    
    last_recv = recv_data;
  }
}

void Serial_Send(String data){

}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void TimerInit(){
    Serial.println("TimerInit");
    BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkTimerFunc);
    BlinkTimer.deleteTimer(BlinkTimerId); 
    BreatheTimerId = BreatheTimer.setInterval(BreatheTime,BreatheTimerFunc);
    BreatheTimer.deleteTimer(ShockTimerId); 
    ShockTimerId = ShockTimer.setInterval(ShockCountTime,ShockTimerFunc);
    ShockTimer.deleteTimer(ShockTimerId);
}

//****************************************Blink Timer****************************************
void BlinkTimerStart(int Neo, int NeoColor){
    blink_neo = Neo;
    blink_color = NeoColor;
    if(Neo == ALLNEO)   BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkAllTimerFunc);
    if(Neo == LEDTAG)   BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkLedtagTimerFunc);
    else                BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkTimerFunc);
}

void BlinkTimerFunc(){
    Serial.println("Blink!");
    if(blink_on == true){
        pixels[blink_neo].lightColor(color[blink_color]);
        blink_on = false;
    }
    else{
        pixels[blink_neo].lightColor(color[BLACK]);
        blink_on = true;
    }
}

void BlinkLedtagTimerFunc(){
    Serial.println("LED TAG Blink!");
    if(blink_on == true){
        LedColor(blink_color);
        pixels[TAG].lightColor(color[blink_color]);
        blink_on = false;
    }
    else{
        LedColor(BLACK);
        pixels[TAG].lightColor(color[BLACK]);
        blink_on = true;
    }
}


void BlinkAllTimerFunc(){
    Serial.println("ALL Blink!");
    if(blink_on == true){
        LedColor(blink_color);
        for(int i=0; i<NeoNum; i++){
            pixels[i].lightColor(color[blink_color]);
        }
        blink_on = false;
    }
    else{
        LedColor(BLACK);
        for(int i=0; i<NeoNum; i++){
            pixels[i].lightColor(color[BLACK]);
        }
        blink_on = true;
    }
}

//****************************************Breathe Timer****************************************
void BreatheTimerStart(int Neo, int NeoColor){
    breathe_neo = Neo;
    breathe_color = NeoColor;
    BreatheTimer.setInterval(BreatheTime,BreatheTimerFunc);
}

void BreatheTimerFunc(){
    Serial.print("Breathe!");
    if(breathe_step >= breathe_step_max)    breathe_step = 0;
    for(int i=0; i<3; i++){
        breathe_color_arr[i] = color[breathe_color][i] /breathe_step_max*breathe_step;
    }
    pixels[breathe_neo].lightColor(breathe_color_arr);
    breathe_step ++;
}

//****************************************Shock Timer****************************************
void ShockTimerFunc(){
    shock_cnt++;
}

//****************************************Connect Timer****************************************
void ConnTimerFunc(){

}