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
#line 29 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
void loop();
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\dfplayer.ino"
void DfpInit();
#line 2 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void EsInit();
#line 10 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void EsOn(bool tf);
#line 25 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Stage(int stage);
#line 54 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Info(int start_point, int end_point);
#line 61 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Loop_Confirm(int loop_num);
#line 80 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Print();
#line 95 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
void ES_Start(int sec, int strength);
#line 2 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void NeopixelInit();
#line 10 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void AllNeoColor(int color_code);
#line 16 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void AllNeoBlink(int color_code, int blink_num, int blink_time);
#line 25 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void LightControl(int color_code, int top_mode, int tag_mode, int bot_mode);
#line 53 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
void LightMode(int neo_code, int color_code, int mode);
#line 2 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void Serial_HandShake();
#line 32 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
void Serial_Read();
#line 108 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
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
#line 95 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void ShockArrTimerFunc();
#line 113 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void RiseTimerStart(int color_code, int time);
#line 128 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void RiseTimerFunc();
#line 141 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void EffectTimerStart(int color_code);
#line 146 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void EffectTimerFunc();
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\wifi.ino"
void WifiInit();
#line 8 "c:\\Github\\Geekble-Electric_Chair_sub\\wifi.ino"
void WifiCheckOTA();
#line 15 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
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
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\dfplayer.ino"
void DfpInit(){
  DFPINIT:
  LightControl(YELLOW, STATIC, STATIC, STATIC);
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

  DFPlayer.volume(20);              // max 30
  DFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  DFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
//****************************************ES SETUP****************************************
void EsInit(){
  Serial.println("EsInit");
  pinMode(ES_SHOCK_PIN, OUTPUT);
  ledcSetup(0, 5000, 0);
  ledcAttachPin(ES_DATA_PIN, 0);
  EsOn(false);
}

void EsOn(bool tf){
  if(tf == true){
    Serial.println("Electric Shock!!!");
    if(IsEsHigh){
      digitalWrite(ES_SHOCK_PIN, LOW);
      IsEsHigh = false;
    }
    else{
      digitalWrite(ES_SHOCK_PIN, HIGH);
      IsEsHigh = true;
    }
  }
}

//****************************************ES Stage****************************************
void ES_Stage(int stage){
  Serial.print("ES STAGE" + (String)(stage) + " START :: ");
  switch (stage){
  case 1:
    ES_Info(1,3);
    ES_Info(4,8);
    ES_Loop_Confirm(4);
    break;
  case 2:
    ES_Info(2,6);
    ES_Info(7,8);
    ES_Loop_Confirm(4);
    break;
  case 3:
    ES_Info(2,6);
    ES_Info(7,8);
    ES_Info(9,10);
    ES_Loop_Confirm(4);
    break;
  case 10:
    ES_Info(1,2);
    ES_Loop_Confirm(1);
  case 0:
  default:
    ShockTimer.deleteTimer(ShockTimerId);
    break;
  }
}

void ES_Info(int start_point, int end_point){    // ES 정보입력 (시점, 종점)
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
    ES_Info(EsArr[i]+loop_end, EsArr[i+1]+loop_end);
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

//****************************************ES Serial****************************************
void ES_Start(int sec, int strength){
  shock_interval = sec;
  if(strength >= 100) strength = 100;
  int ShockLevel = ShockLevel_max * strength/100;

  ledcWrite(0, ShockLevel);
  ShockTimer.deleteTimer(ShockTimerId);
  ShockTimerId = ShockTimer.setInterval(ShockCountTime,ShockTimerFunc);
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
//****************************************Neopixel SETUP****************************************
void NeopixelInit(){
  Serial.println("NeopixelInit");
  for(int i=0; i<NeoNum; i++){
    pixels[i].begin();
  }
  LightControl(WHITE, STATIC, STATIC, STATIC);
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
  EffectTimer.deleteTimer(EffectTimerId);

  if(blink_num <= 1){
    if(top_mode == STATIC)
      EffectTimerStart(color_code);
    else
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
      RiseTimerStart(color_code, 15);
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
  if(subTTGO.available()){
    if(subTTGO.read() == '@'){
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
        Serial.println("connection ERROR");
        Serial.println("from main : " + recv_data);
        goto RECONNECT_TTGO;
      }
    }
    else goto RECONNECT_TTGO;
  }
}

void Serial_Read(){
  if(subTTGO.available()){
    if(subTTGO.read() == '@'){
      String recv_data = subTTGO.readStringUntil(' ');
      Serial.println("from main : " + recv_data);
      
      EsOn(false);
      DFPlayer.pause();
      RiseCNT = 0;
      RiseTimer.deleteTimer(RiseTimerId);
      ShockTimer.deleteTimer(ShockTimerId);
      
      if(recv_data == "connect"){
        SerialSend("ok");
      }
      else if(recv_data == "setting")         LightControl(WHITE,  STATIC, STATIC, STATIC);
      else if(recv_data == "ready")       		LightControl(RED,    STATIC, STATIC, BREATHE);
      else if(recv_data == "activate_wait")   LightControl(YELLOW, STATIC, STATIC, BREATHE);
      else if(recv_data == "activate_t1")		  LightControl(GREEN,  STATIC, STATIC, BREATHE);
      else if(recv_data == "activate_t2") 	  LightControl(GREEN,  BLINK,  BLINK,  BREATHE);
      else if(recv_data == "activate_t3") 	  LightControl(BLUE,	 STATIC, STATIC, BREATHE);
      else if(recv_data == "stage1"){
        LightControl(BLUE,   STATIC, STATIC, BREATHE);
        EsStage = 1;
        Serial.println("curr_EsStage:" + (String)(curr_EsStage) + " / EsStage:" + (String)(EsStage));
        if(curr_EsStage != EsStage){
          Serial.println("diff");
          DFPlayer.playLargeFolder(2,1);
        }
        else{
          Serial.println("same");
          ES_Start(10, 40);
          DFPlayer.start();
        }
      }
      else if(recv_data == "stage2"){
        LightControl(BLUE,   STATIC, STATIC, BREATHE);
        EsStage = 2;
        Serial.println("curr_EsStage:" + (String)(curr_EsStage) + " / EsStage:" + (String)(EsStage));
        if(curr_EsStage != EsStage){
          DFPlayer.playLargeFolder(2,2);
        }
        else{
          ES_Start(5, 70);
          DFPlayer.start();
        }
      }
      else if(recv_data == "stage3"){
        LightControl(BLUE,   STATIC, STATIC, BREATHE);
        EsStage = 3;
        Serial.println("curr_EsStage:" + (String)(curr_EsStage) + " / EsStage:" + (String)(EsStage));
        if(curr_EsStage != EsStage){
          DFPlayer.playLargeFolder(2,3);
        }
        else{
          ES_Start(5, 100);
          DFPlayer.start();
        }
      }
      else if(recv_data == "cool")						LightControl(RED,    STATIC, STATIC, BREATHE);
      else if(recv_data == "rescue")				 {LightControl(GREEN,  STATIC, BLINK,  RISE);     DFPlayer.start();}
      else if(recv_data == "rescue_suc")		 {AllNeoBlink(GREEN, 4, 500);   LightControl(RED, STATIC, STATIC, BREATHE);}
      else if(recv_data == "rescue_fail")		 {DFPlayer.start();             AllNeoBlink(RED, 5, 250);}
      else if(recv_data == "shock"){
        DFPlayer.start();
        Serial.println("Shock");
        if(EsStage == 1)          ES_Start(10, 40);
        else if(EsStage == 2)     ES_Start(5, 70);
        else if(EsStage == 3)     ES_Start(5, 100);
        curr_EsStage = EsStage;
      }
      else    Serial.println("[ERROR]" + recv_data);
    }
  }
}

void SerialSend(String data){
  String SendData = "@" + data + " ";
  subTTGO.print(SendData);
  Serial.println("to Main : " + SendData);
}
// Serial.println("curr_EsStage:" + (String)(curr_EsStage) + " / EsStage:" + (String)(EsStage));
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
    if(shock_cnt >= shock_interval){
        EsOn(true);
        shock_cnt = 0;
    }
    else{
        Serial.print("CNT:" + (String)(shock_cnt) + " ");
        shock_cnt ++;
    }
}

void ShockArrTimerFunc(){
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

    for(int n=0; n<NumPixels[BOT]; n++)
        pixels[BOT].setPixelColor(n, color[BLUE][0], color[BLUE][1], color[BLUE][2]);
    for(int n=0; n<STRpoint; n++)
        pixels[BOT].setPixelColor(n, color[RiseColor][0], color[RiseColor][1], color[RiseColor][2]);
    for(int n=ENDpoint; n<NumPixels[BOT]; n++)
        pixels[BOT].setPixelColor(n, color[RiseColor][0], color[RiseColor][1], color[RiseColor][2]);
    // pixels[BOT].setPixelColor(MIDpoint, color[RED][0], color[RED][1], color[RED][2]);
    pixels[BOT].show();
    RiseTimer.setInterval(RiseTime,RiseTimerFunc);
}

void RiseTimerFunc(){
    if(RiseCNT > RiseStep){
        pixels[BOT].lightColor(color[RiseColor]);
        RiseTimer.deleteTimer(RiseTimerId);
        RiseCNT = 0;
    }
    pixels[BOT].setPixelColor(STRpoint + RiseCNT, color[RiseColor][0], color[RiseColor][1], color[RiseColor][2]);
    pixels[BOT].setPixelColor(ENDpoint - RiseCNT, color[RiseColor][0], color[RiseColor][1], color[RiseColor][2]);
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
    int EffNeoNum1 = 4;
    int EffNeoNum2 = 6;
    int EffNeoNum3 = 4;
    int EffColorArr0[3] = {0};
    int EffColorArr1[3] = {0};
    int EffColorArr2[3] = {0};
    int EffColorArr3[3] = {0};

    for(int i=0; i<3; i++)        EffColorArr0[i] = color[EffColor][i] *1/7;    // 배경색
    for(int i=0; i<3; i++)        EffColorArr1[i] = color[EffColor][i] *1/2;    // 제 1색
    for(int i=0; i<3; i++)        EffColorArr2[i] = color[EffColor][i] *1/1;    // 제 2색
    for(int i=0; i<3; i++)        EffColorArr3[i] = color[EffColor][i] *1/2;    // 제 3색

    int EffArr[50] = {0};
    int EffNum = EffNeoNum1+EffNeoNum2+EffNeoNum3;
    for(int arr=0; arr<EffNum; arr++){
        int Eff_NeoPoint = EffPoint - arr;
        if(Eff_NeoPoint<0)  Eff_NeoPoint = NumPixels[TOP]+Eff_NeoPoint;
        EffArr[arr] = Eff_NeoPoint;
    }

    for(int n=0; n<NumPixels[TOP]; n++)
        pixels[TOP].setPixelColor(n, EffColorArr0[0], EffColorArr0[1], EffColorArr0[2]);
    for(int n=0; n<EffNeoNum1; n++)
        pixels[TOP].setPixelColor(EffArr[n], EffColorArr1[0], EffColorArr1[1], EffColorArr1[2]);
    for(int n=EffNeoNum1; n<EffNeoNum1+EffNeoNum2; n++)
        pixels[TOP].setPixelColor(EffArr[n], EffColorArr2[0], EffColorArr2[1], EffColorArr2[2]);
    for(int n=EffNeoNum1+EffNeoNum2; n<EffNeoNum1+EffNeoNum2+EffNeoNum3; n++)
        pixels[TOP].setPixelColor(EffArr[n], EffColorArr3[0], EffColorArr3[1], EffColorArr3[2]);
    pixels[TOP].show();
    EffPoint ++;
}
#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\wifi.ino"
void WifiInit(){
  LightControl(RED, STATIC, STATIC, STATIC);
  // has2wifi.Setup("KT_GiGA_6C64","ed46zx1198");
  has2wifi.Setup("badland");
  // has2wifi.Setup("city");
}

void WifiCheckOTA(){
  // if()
  // has2wifi.FirmwareUpdate();
}
