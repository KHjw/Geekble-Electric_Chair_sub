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