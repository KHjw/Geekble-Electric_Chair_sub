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