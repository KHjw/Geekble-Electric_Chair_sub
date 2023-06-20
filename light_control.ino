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
  if(step_cnt > step)  step_cnt = step;
  pixels[neo_code].lightColor(color[BLACK]);
  pixels[neo_code].lightColor(color[color_code], first_step + step_cnt*step_neonum);
}

//****************************************Light Control****************************************
void LightControl(int color_code, int top_mode, int tag_mode, int bot_mode){
  int blink_num = 0;
  if(top_mode == BLINK)   blink_num++;
  if(tag_mode == BLINK)   blink_num++;
  if(bot_mode == BLINK)   blink_num++;

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