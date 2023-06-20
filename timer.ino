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
    if(breathe_step >= breathe_step_max)    breathe_step = 0;
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

//****************************************Connect Timer****************************************
void ConnTimerFunc(){
}