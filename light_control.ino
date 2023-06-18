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