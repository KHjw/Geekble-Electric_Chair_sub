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
  TimerInit();
  NeopixelInit();
  LightControl(WHITE, STATIC, STATIC, STATIC);
  EsInit();
  Serial_HandShake();
  Serial.println("===============TTGO INITALIZED======== =======");
}

void loop(){
  Serial_Read();
  ShockTimer.run();
  BlinkTimer.run();
  BreatheTimer.run();
}
# 1 "c:\\Github\\Geekble-Electric_Chair_sub\\electric_shock.ino"
//****************************************ES SETUP****************************************
void EsInit(){
  Serial.println("EsInit");
  pinMode(15, 0x03);
  EsOn(false);
}

void EsOn(bool tf){
  if(tf == true){
    Serial.println("Es On");
    digitalWrite(15, 0x1);
    IsEsOn = true;
  }
  else{
    Serial.println("Es Off");
    digitalWrite(15, 0x0);
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
    ES_Loop_Confirm(1);
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
  loop_num --;
  if(loop_num < 1) loop_num = 0;

  int loop_end = EsArr[EsArr_cnt-1];
  for(int i=0; i<loop_num * loop_end; i+=2){
    ES_Control(EsArr[i]+loop_end, EsArr[i+1]+loop_end);
    if(EsArr_cnt > EsArr_max) goto ES_START;
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

void NeoRise(int neo_code, int color_code, int step, int step_cnt){
  int step_neonum = NumPixels[neo_code]/step;
  int first_step = step_neonum + NumPixels[neo_code]%step;
  if(step_cnt > step) step_cnt = step;
  pixels[neo_code].lightColor(color[BLACK]);
  pixels[neo_code].lightColor(color[color_code], first_step + step_cnt*step_neonum);
}

//****************************************Light Control****************************************
void LightControl(int color_code, int top_mode, int tag_mode, int bot_mode){
  int blink_num = 0;
  if(top_mode == BLINK) blink_num++;
  if(tag_mode == BLINK) blink_num++;
  if(bot_mode == BLINK) blink_num++;

  if(blink_num <= 1){
    LightMode(TOP, color_code, top_mode);
    LightMode(TAG, color_code, tag_mode);
    LightMode(BOT, color_code, bot_mode);
  }
  else if(blink_num == 2){
    BlinkTimer.deleteTimer(BlinkTimerId);
    BlinkTimerStart(LEDTAG, color_code);
    LightMode(BOT, color_code, bot_mode);
  }
  else if(blink_num == 3){
    BlinkTimer.deleteTimer(BlinkTimerId);
    BlinkTimerStart(ALLNEO, color_code);
  }
}

void LightMode(int neo_code, int color_code, int mode){
  switch(mode){
    case STATIC:
      pixels[neo_code].lightColor(color[color_code]);
      break;
    case BLINK:
      BlinkTimer.deleteTimer(BlinkTimerId);
      BlinkTimerStart(neo_code, color_code);
      break;
    case BREATHE:
      BreatheTimer.deleteTimer(BreatheTimerId);
      BreatheTimerStart(neo_code, color_code);
      break;
    case RISE:
      NeoRise(neo_code, color_code, 6, 0);
      break;
    default:
      pixels[neo_code].lightColor(color[BLACK]);
      break;
  }
}
# 1 "c:\\Github\\Geekble-Electric_Chair_sub\\serial.ino"
//****************************************Serial Communication****************************************
void SerialInit(){
}

void Serial_HandShake(){
  Serial.println("Serial Handshake Init");
  subTTGO.begin(9600, 0x800001c, 18, 19);
  RECONNECT_TTGO:
  delay(100);
  Serial.println("Connecting to TTGO");
  subTTGO.print("connect ");
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil(' ');
    if(recv_data == "connect"){
      Serial.println("recv CONNECT");
      subTTGO.print("ok ");
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
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil(' ');
    Serial.println("from main : " + recv_data);
    if(recv_data == "connect"){
      subTTGO.print("ok ");
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
    else BlinkTimerId = BlinkTimer.setInterval(BlinkTime,BlinkTimerFunc);
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
    if(breathe_step >= breathe_step_max) breathe_step = 0;
    for(int i=0; i<3; i++){
        breathe_color_arr[i] = color[breathe_color][i] /breathe_step_max*breathe_step;
    }
    pixels[breathe_neo].lightColor(breathe_color_arr);
    breathe_step ++;
    // if(breathe_step >= breathe_step_max)
    //    breathe_step ++;
    // else 
    //    breathe_step --;
}

//****************************************Shock Timer****************************************
void ShockTimerFunc(){
    Serial.print("CNT:" + (String)(shock_cnt) + " ");

    if(shock_cnt == EsArr[shock_arr]){
        if((shock_arr%2) == 0) EsOn(true);
        else EsOn(false);
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

//****************************************Connect Timer****************************************
void ConnTimerFunc(){
}
