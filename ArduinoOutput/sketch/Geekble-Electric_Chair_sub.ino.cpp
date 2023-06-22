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
#line 27 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
void loop();
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\dfplayer.ino"
void DfpInit();
#line 2 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void EsInit();
#line 8 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void EsOn(bool tf);
#line 22 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Stage(int stage);
#line 51 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Control(int start_point, int end_point);
#line 58 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Loop_Confirm(int loop_num);
#line 77 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Print();
#line 2 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void NeopixelInit();
#line 9 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void AllNeoColor(int color_code);
#line 15 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void AllNeoBlink(int color_code, int blink_num, int blink_time);
#line 24 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void LightControl(int color_code, int top_mode, int tag_mode, int bot_mode);
#line 52 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void LightMode(int neo_code, int color_code, int mode);
#line 2 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void Serial_HandShake();
#line 32 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void Serial_RestartCheck();
#line 46 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void Serial_Read();
#line 82 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void SerialSend(String data);
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void TimerInit();
#line 16 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BlinkTimerStart(int Neo, int NeoColor);
#line 24 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BlinkTimerFunc();
#line 35 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BlinkTopTimerFunc();
#line 48 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BlinkAllTimerFunc();
#line 64 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BreatheTimerStart(int Neo, int NeoColor);
#line 70 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void BreatheTimerFunc();
#line 84 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void ShockTimerFunc();
#line 102 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void RiseTimerStart(int color_code, int time);
#line 113 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void RiseTimerFunc();
#line 126 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void EffectTimerStart(int color_code);
#line 131 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void EffectTimerFunc();
#line 15 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
void setup(){
  Serial.begin(115200);
  Serial.println("===============TTGO INIT===============");
  TimerInit();
  NeopixelInit();
  LightControl(WHITE, STATIC, STATIC, STATIC);
  EsInit();
  Serial_HandShake();
  DfpInit();
  Serial.println("===============TTGO INITALIZED===============");
}

void loop(){
  Serial_Read();
  ShockTimer.run();
  BlinkTimer.run();
  BreatheTimer.run();
  RiseTimer.run();
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\dfplayer.ino"
void DfpInit(){
  DFPINIT:
  serialDFP.begin(9600, SERIAL_8N1, DFP_RX, DFP_TX);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if(!DFPlayer.begin(serialDFP)){
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    delay(500);
    goto DFPINIT;
  }
  Serial.println(F("DFPlayer Mini online."));

  DFPlayer.volume(22);              // max 30
  DFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  DFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
//****************************************ES SETUP****************************************
void EsInit(){
  Serial.println("EsInit");
  pinMode(ES_PIN, OUTPUT);
  EsOn(false);
}

void EsOn(bool tf){
  if(tf == true){
    Serial.println("Es On");
    digitalWrite(ES_PIN, HIGH);
    IsEsOn = true;
  }
  else{
    Serial.println("Es Off");
    digitalWrite(ES_PIN, LOW);
    IsEsOn = false;
  }
}

//****************************************ES Stage****************************************
void ES_Stage(int stage){
  Serial.print("ES STAGE" + (String)(stage) + " START :: ");
  switch (stage){
  case 1:
    ES_Control(1,3);
    ES_Control(4,8);
    ES_Loop_Confirm(4);
    break;
  case 2:
    ES_Control(2,6);
    ES_Control(7,8);
    ES_Loop_Confirm(4);
    break;
  case 3:
    ES_Control(2,6);
    ES_Control(7,8);
    ES_Control(9,10);
    ES_Loop_Confirm(4);
    break;
  case 10:
    ES_Control(1,2);
    ES_Loop_Confirm(1);
  case 0:
  default:
    ShockTimer.deleteTimer(ShockTimerId);
    break;
  }
}

void ES_Control(int start_point, int end_point){    // ES 정보입력 (시점, 종점)
  EsArr[EsArr_cnt] = start_point;
  EsArr_cnt ++;
  EsArr[EsArr_cnt] = end_point;
  EsArr_cnt ++;
}

void ES_Loop_Confirm(int loop_num){                 // ES 입력정보 적용
  loop_num --;
  if(loop_num < 1)    loop_num = 0;

  int loop_end = EsArr[EsArr_cnt-1];
  for(int i=0; i<loop_num * loop_end; i+=2){
    ES_Control(EsArr[i]+loop_end, EsArr[i+1]+loop_end);
    if(EsArr_cnt > EsArr_max)  goto ES_START;
  }
  ES_START:
  ES_Print();
  shock_end = EsArr[EsArr_cnt-1]; 
  EsArr_cnt = 0;
  shock_cnt = 0;
  shock_arr = 0;
  ShockTimer.deleteTimer(ShockTimerId);
  ShockTimerId = ShockTimer.setInterval(ShockCountTime,ShockTimerFunc);
}

void ES_Print(){
  String EsData;
  for(int i=0; i<EsArr_cnt; i++){
    EsData += EsArr[i]; 
    if((i%2) == 1) 
      EsData += "/";
    else
      EsData += " ";
  }
  Serial.print("#EsData : " + EsData);
  Serial.print(" #ShockEnd : " + (String)(shock_end));
  Serial.println("");
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

void AllNeoBlink(int color_code, int blink_num, int blink_time){
  for(int n=0; n<blink_num; n++){
    AllNeoColor(BLACK);
    delay(blink_time);
    AllNeoColor(color_code);
    delay(blink_time);
  }
}
//****************************************Light Control****************************************
void LightControl(int color_code, int top_mode, int tag_mode, int bot_mode){
  int blink_num = 0;
  if(top_mode == BLINK)   blink_num++;
  if(tag_mode == BLINK)   blink_num++;
  if(bot_mode == BLINK)   blink_num++;

  BreatheTimer.deleteTimer(BreatheTimerId);
  BlinkTimer.deleteTimer(BlinkTimerId);
  RiseTimer.deleteTimer(RiseTimerId);

  if(top_mode != STATIC)    EffectTimer.deleteTimer(EffectTimerId);
  else    EffectTimerStart(color_code);
  

  if(blink_num <= 1){
    LightMode(TOP, color_code, top_mode);
    LightMode(TAG, color_code, tag_mode);
    LightMode(BOT, color_code, bot_mode);
  }
  else if(blink_num == 2){
    BlinkTimerStart(TOPTAG, color_code);
    LightMode(BOT, color_code, bot_mode);
  }
  else if(blink_num == 3){
    BlinkTimerStart(ALLNEO, color_code);
  }
}

void LightMode(int neo_code, int color_code, int mode){
  switch(mode){
    case STATIC:
      pixels[neo_code].lightColor(color[color_code]);
      break;
    case BLINK:
      BlinkTimerStart(neo_code, color_code);
      break;
    case BREATHE:
      BreatheTimerStart(neo_code, color_code);
      break;
    case RISE:
      RiseTimerStart(color_code, 5);
      break;
    default:
      pixels[neo_code].lightColor(color[BLACK]);
      break;
  }
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
//****************************************Serial Communication****************************************
void Serial_HandShake(){
  Serial.println("Serial Handshake Init");
  subTTGO.begin(9600, SERIAL_8N1, SUBTTGO_RX_PIN, SUBTTGO_TX_PIN);
  RECONNECT_TTGO:
  delay(100);
  Serial.println("Connecting to TTGO");
  SerialSend("connect");
  if(subTTGO.read() == '@'){
    if(subTTGO.available()){
      String recv_data = subTTGO.readStringUntil(' ');
      if(recv_data == "connect"){
        Serial.println("recv CONNECT");
        SerialSend("ok");
        LightControl(BLUE, STATIC, STATIC, STATIC);
        goto RECONNECT_TTGO;
      }
      else if(recv_data == "ok"){
        Serial.println("TTGO CONNECTED");
        LightControl(PURPLE, STATIC, STATIC, STATIC);
      }
      else{
        Serial.println("from main : " + recv_data);
        Serial.println("connection failed");
        goto RECONNECT_TTGO;
      }
    }
    else goto RECONNECT_TTGO;
  }
}

void Serial_RestartCheck(){
  Serial.print("0");
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil(' ');
    if(recv_data == "connect"){
      SerialSend("ok");
      Serial.println("send CONNECT");
    }
    else 
      Serial.println("from main : " + recv_data);
  }
  delay(500);
}

void Serial_Read(){
  if(subTTGO.available()){
    EsOn(false);
    EsStage = 0;
    if(subTTGO.read() == '@'){
      String recv_data = subTTGO.readStringUntil(' ');
      Serial.println("from main : " + recv_data);
      if(recv_data == "connect"){
        SerialSend("ok");
      }
      else if(recv_data == "setting")         LightControl(WHITE,  STATIC, STATIC, STATIC);
      else if(recv_data == "ready")       		LightControl(RED,    STATIC, STATIC, BREATHE);
      else if(recv_data == "activate_wait")   LightControl(YELLOW, STATIC, STATIC, BREATHE);
      else if(recv_data == "activate_t1")		 {LightControl(GREEN,  STATIC, STATIC, BREATHE);}
      else if(recv_data == "activate_t2") 	 {LightControl(GREEN,  BLINK,  BLINK,  BREATHE);}
      else if(recv_data == "activate_t3") 	 {LightControl(BLUE,	 STATIC, STATIC, BREATHE);}
      else if(recv_data == "stage1")     		 {LightControl(BLUE,   STATIC, STATIC, BREATHE);  EsStage = 1;  DFPlayer.playLargeFolder(2,1);}
      else if(recv_data == "stage2")     		 {LightControl(BLUE,   STATIC, STATIC, BREATHE);  EsStage = 2;  DFPlayer.playLargeFolder(2,2);}
      else if(recv_data == "stage3")				 {LightControl(BLUE,   STATIC, STATIC, BREATHE);  EsStage = 3;  DFPlayer.playLargeFolder(2,3);}
      else if(recv_data == "cool")						LightControl(RED,    STATIC, STATIC, BREATHE);
      else if(recv_data == "rescue")					LightControl(GREEN,  STATIC, BLINK,  RISE);
      else if(recv_data == "rescue_suc")		 {AllNeoBlink(GREEN, 4, 500); RiseTimer.deleteTimer(RiseTimerId); LightControl(RED,    STATIC, STATIC, BREATHE);}
      else if(recv_data == "rescue_fail")		 {AllNeoBlink(RED, 5, 250);   RiseTimer.deleteTimer(RiseTimerId);}
      else if(recv_data == "shock"){
        // if(curr_EsStage != EsStage){
        //   if(EsStage == 1)          ES_Stage(1);
        //   else if(EsStage == 2)     ES_Stage(2);
        //   else if(EsStage == 3)     ES_Stage(3);
        //   else                      DFPlayer.pause();
        //   curr_EsStage = EsStage;
      }
      else                                    Serial.println("from main : " + recv_data);
    }
  }
}

void SerialSend(String data){
  String SendData = "@";
  SendData += data;
  SendData += " ";
  SerialSend(SendData);
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void TimerInit(){
    Serial.println("TimerInit");
    BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkTimerFunc);
    BlinkTimer.deleteTimer(BlinkTimerId); 
    BreatheTimerId = BreatheTimer.setInterval(BreatheTime,BreatheTimerFunc);
    BreatheTimer.deleteTimer(BreatheTimerId); 
    RiseTimerId = RiseTimer.setInterval(RiseTime,RiseTimerFunc);
    RiseTimer.deleteTimer(RiseTimerId);
    ShockTimerId = ShockTimer.setInterval(ShockCountTime,ShockTimerFunc);
    ShockTimer.deleteTimer(ShockTimerId);
    EffectTimerId = EffectTimer.setInterval(EffectTime,EffectTimerFunc);
    EffectTimer.deleteTimer(EffectTimerId);
}

//****************************************Blink Timer****************************************
void BlinkTimerStart(int Neo, int NeoColor){
    blink_neo = Neo;
    blink_color = NeoColor;
    if(Neo == ALLNEO)   BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkAllTimerFunc);
    if(Neo == TOPTAG)   BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkTopTimerFunc);
    else                BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkTimerFunc);
}

void BlinkTimerFunc(){
    if(blink_on == true){
        pixels[blink_neo].lightColor(color[blink_color]);
        blink_on = false;
    }
    else{
        pixels[blink_neo].lightColor(color[BLACK]);
        blink_on = true;
    }
}

void BlinkTopTimerFunc(){
    if(blink_on == true){
        pixels[TOP].lightColor(color[blink_color]);
        pixels[TAG].lightColor(color[blink_color]);
        blink_on = false;
    }
    else{
        pixels[TOP].lightColor(color[BLACK]);
        pixels[TAG].lightColor(color[BLACK]);
        blink_on = true;
    }
}

void BlinkAllTimerFunc(){
    if(blink_on == true){
        for(int i=0; i<NeoNum; i++){
            pixels[i].lightColor(color[blink_color]);
        }
        blink_on = false;
    }
    else{
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
    if(breathe_step >= breathe_step_max)    IsCountUP = false;
    else if(breathe_step <= 0)              IsCountUP = true;

    for(int i=0; i<3; i++){
        breathe_color_arr[i] = color[breathe_color][i] /breathe_step_max*breathe_step;
    }
    pixels[breathe_neo].lightColor(breathe_color_arr);

    if(IsCountUP)   breathe_step ++;
    else            breathe_step --;
}

//****************************************Shock Timer****************************************
void ShockTimerFunc(){
    Serial.print("CNT:" + (String)(shock_cnt) + " ");

    if(shock_cnt == EsArr[shock_arr]){
        if((shock_arr%2) == 0)  EsOn(true);
        else                    EsOn(false);
        shock_arr++;
    }
    if(shock_cnt == shock_end){
        Serial.println("ES KILL");
        ShockTimer.deleteTimer(ShockTimerId);
        EsOn(false);
        shock_end = 0;
    }
    shock_cnt++;
}

//****************************************Rise Timer****************************************
void RiseTimerStart(int color_code, int time){      // time=초
    RiseColor = color_code;
    RiseTime = time *1000/RiseStep;

    pixels[BOT].lightColor(color[BLUE]);
    pixels[BOT].lightColor(color[RiseColor], ENDpoint);
    pixels[BOT].lightColor(color[BLUE], STRpoint + (ENDpoint-STRpoint)%2);     // 초기값 설정
    
    RiseTimer.setInterval(RiseTime,RiseTimerFunc);
}

void RiseTimerFunc(){
    if(RiseCNT > RiseStep){
        pixels[BOT].lightColor(color[RiseColor]);
        RiseTimer.deleteTimer(RiseTimerId);
        RiseCNT = 0;
    }
    pixels[BOT].setPixelColor(STRpoint - (RiseCNT/2), color[RiseColor][0], color[RiseColor][1], color[RiseColor][2]);
    pixels[BOT].setPixelColor(ENDpoint - (RiseCNT/2), color[RiseColor][0], color[RiseColor][1], color[RiseColor][2]);
    pixels[BOT].show();
    RiseCNT++;
}

//****************************************Effect Timer****************************************
void EffectTimerStart(int color_code){
    EffColor = color_code;
    EffectTimerId = EffectTimer.setInterval(EffectTime,EffectTimerFunc);
}

void EffectTimerFunc(){
    if(EffPoint > NumPixels[TOP])   EffPoint = 0;

    int EffArr[5] = {0};
    
    for(int arr=0; arr<5; arr++){
        int Eff_NeoPoint = EffPoint - arr;
        if(Eff_NeoPoint<0)  Eff_NeoPoint = NumPixels[TOP]+Eff_NeoPoint;
        EffArr[arr] = Eff_NeoPoint;
    }

    pixels[TOP].lightColor(color[EffColor]);

    for(int i=0; i<3; i++){
        EffColorArr[i] = color[EffColor][i] *2/3;
    }

    for(int n; n<5; n++){
        pixels[TOP].setPixelColor(EffArr[n], EffColorArr[0], EffColorArr[1], EffColorArr[2]);
    }
    pixels[TOP].show();
    EffPoint ++;
}
