# 1 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
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
# 13 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino"
# 14 "c:\\Github\\Geekble-Electric_Chair_sub\\Geekble-Electric_Chair_sub.ino" 2

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
# 1 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
//****************************************ES SETUP****************************************
void EsInit(){
  Serial.println("EsInit");
  pinMode(2, 0x03);
  EsOn(false);
}

void EsOn(bool tf){
  if(tf == true){
    Serial.println("ES!!!");
    digitalWrite(2, 0x1);
    IsEsOn = true;
  }
  else{
    digitalWrite(2, 0x0);
    IsEsOn = false;
  }
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
  case 10:
    ES_Control(1,2);
    ES_Loop_Confirm(1);
  case 0:
  default:
    ShockTimer.deleteTimer(ShockTimerId);
    break;
  }
}

void ES_Control(int start_point, int end_point){ // ES 정보입력 (시점, 종점)
  EsArr[EsArr_cnt] = start_point;
  EsArr_cnt ++;
  EsArr[EsArr_cnt] = end_point;
  EsArr_cnt ++;
}

void ES_Loop_Confirm(int loop_num){ // ES 입력정보 적용
  if(loop_num < 1) loop_num = 0;
  int loop_end = EsArr_cnt/2;
  for(int i=0; i<loop_num * loop_end; i++){
    ES_Control(EsArr[i],EsArr[i+1]);
    if(EsArr_cnt > EsArr_max) goto ES_START;
  }
  ES_START:
  ES_Print();
  shock_end = EsArr_cnt;
  EsArr_cnt = 0;
  shock_cnt = 0;
  shock_arr = 0;
  ShockTimer.deleteTimer(ShockTimerId);
  ShockTimerId = ShockTimer.setInterval(ShockCountTime,ShockTimerFunc);
}

void ES_Print(){
  String EsData;
  for(int i; i<EsArr_cnt; i++)
    EsData += EsArr[i];
  Serial.println(EsData);
}
# 1 "c:\\Github\\Geekble-Electric_Chair_sub\\light_control.ino"
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
  pinMode(12, 0x03);
  pinMode(13, 0x03);
  pinMode(15, 0x03);
}

void LedColor(int color_code){
  switch(color_code){
    case RED:
      digitalWrite(12, 0x1);
      digitalWrite(13, 0x0);
      digitalWrite(15, 0x0);
      break;
    case GREEN:
      digitalWrite(12, 0x0);
      digitalWrite(13, 0x1);
      digitalWrite(15, 0x0);
      break;
    case BLUE:
      digitalWrite(12, 0x0);
      digitalWrite(13, 0x0);
      digitalWrite(15, 0x1);
      break;
    case YELLOW:
      digitalWrite(12, 0x1);
      digitalWrite(13, 0x1);
      digitalWrite(15, 0x0);
      break;
    case PURPLE:
      digitalWrite(12, 0x1);
      digitalWrite(13, 0x0);
      digitalWrite(15, 0x1);
      break;
    case WHITE:
      digitalWrite(12, 0x1);
      digitalWrite(13, 0x1);
      digitalWrite(15, 0x1);
      break;
    case BLACK:
    default:
      digitalWrite(12, 0x0);
      digitalWrite(13, 0x0);
      digitalWrite(15, 0x0);
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
# 1 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
//****************************************Serial Communication****************************************
void SerialInit(){
}

void Serial_HandShake(){
  Serial.println("Serial Handshake Init");
  subTTGO.begin(9600, 0x800001c, 12, 13);
  RECONNECT_TTGO:
  delay(100);
  Serial.println("Connecting to TTGO");
  subTTGO.print("connect ");
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil(' ');
    if(recv_data == "connect"){
      Serial.println("recv CONNECT");
      subTTGO.print("ok ");
      goto RECONNECT_TTGO;
    }
    else if(recv_data == "ok"){
      Serial.println("TTGO CONNECTED");
    }
    else{
      Serial.println("from main : " + recv_data);
      Serial.println("connection failed");
      goto RECONNECT_TTGO;
    }
  }
  else goto RECONNECT_TTGO;
}

void Serial_RestartCheck(){
  Serial.print("0");
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil(' ');
    if(recv_data == "connect"){
      subTTGO.print("ok ");
      Serial.println("send CONNECT");
    }
    else
      Serial.println("from main : " + recv_data);
  }
  delay(500);
}

void Serial_Read(){
  Serial.print("0");
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil(' ');
    if(recv_data == "connect"){
      subTTGO.print("ok ");
      LightControl(PURPLE, STATIC, STATIC, STATIC);
      Serial.println("from main : " + recv_data);
    }
    else if(recv_data == "setting") LightControl(WHITE, STATIC, STATIC, STATIC);
    else if(recv_data == "ready") LightControl(RED, STATIC, STATIC, BREATHE);
    else if(recv_data == "activate_wait") LightControl(YELLOW, STATIC, STATIC, BREATHE);
    else if(recv_data == "activate_t1") LightControl(GREEN, STATIC, STATIC, BREATHE);
    else if(recv_data == "activate_t2") LightControl(GREEN, BLINK, BLINK, BREATHE);
    else if(recv_data == "activate_t3") LightControl(BLUE, STATIC, STATIC, BREATHE);
    else if(recv_data == "stage1") {LightControl(BLUE, STATIC, STATIC, BREATHE);
                                            ES_Stage(1);}
    else if(recv_data == "stage2") {LightControl(BLUE, STATIC, STATIC, BREATHE);
                                            ES_Stage(2);}
    else if(recv_data == "stage3") {LightControl(BLUE, STATIC, STATIC, BREATHE);
                                            ES_Stage(3);}
    else if(recv_data == "cool") LightControl(RED, STATIC, STATIC, BREATHE);
    else if(recv_data == "rescue") LightControl(GREEN, STATIC, BLINK, RISE);
    else if(recv_data == "rescue_suc") LightControl(GREEN, STATIC, STATIC, STATIC);
    else if(recv_data == "rescue_fail") LightControl(RED, BLINK, BLINK, BLINK);
    else Serial.println("from main : " + recv_data);
    last_recv = recv_data;
  }
}
# 1 "c:\\Github\\Geekble-Electric_Chair_sub\\timer.ino"
void TimerInit(){
    Serial.println("TimerInit");
    BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkTimerFunc);
    BlinkTimer.deleteTimer(BlinkTimerId);
    BreatheTimerId = BreatheTimer.setInterval(BreatheTime,BreatheTimerFunc);
    BreatheTimer.deleteTimer(BreatheTimerId);
    ShockTimerId = ShockTimer.setInterval(ShockCountTime,ShockTimerFunc);
    ShockTimer.deleteTimer(ShockTimerId);
}

//****************************************Blink Timer****************************************
void BlinkTimerStart(int Neo, int NeoColor){
    blink_neo = Neo;
    blink_color = NeoColor;
    if(Neo == ALLNEO) BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkAllTimerFunc);
    if(Neo == LEDTAG) BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkLedtagTimerFunc);
    else BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkTimerFunc);
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
    if(breathe_step >= breathe_step_max) breathe_step = 0;
    for(int i=0; i<3; i++){
        breathe_color_arr[i] = color[breathe_color][i] /breathe_step_max*breathe_step;
    }
    pixels[breathe_neo].lightColor(breathe_color_arr);
    breathe_step ++;
}

//****************************************Shock Timer****************************************
void ShockTimerFunc(){
    if(shock_cnt == shock_end){
        ShockTimer.deleteTimer(ShockTimerId);
        shock_end = 0;
    }
    else if(shock_cnt == EsArr[shock_arr]){
        if((shock_arr%2) == 0) digitalWrite(2, 0x1);
        else digitalWrite(2, 0x0);
        shock_arr++;
    }
    shock_cnt++;
}

//****************************************Connect Timer****************************************
void ConnTimerFunc(){

}
