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
    if(breathe_step >= breathe_step_max)    breathe_step = 0;
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
        if((shock_arr%2) == 0)  digitalWrite(ES_PIN, HIGH);
        else                    digitalWrite(ES_PIN, LOW);
        shock_arr++;
    }
    shock_cnt++;
}

//****************************************Connect Timer****************************************
void ConnTimerFunc(){

}