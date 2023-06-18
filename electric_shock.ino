//****************************************ES SETUP****************************************
void EsInit(){
  Serial.println("EsInit");
  pinMode(ES_PIN, OUTPUT);
  EsOn(false);
}

void EsOn(bool tf){
  if(tf == true){
    digitalWrite(ES_PIN, HIGH);
    IsEsOn = true;
  }
  else{
    digitalWrite(ES_PIN, LOW);
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
  case 0:
  default:
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
  int loop_end = EsArr_cnt/2;
  for(int i=0; i<loop_num * loop_end; i++){
    ES_Control(EsArr[i],EsArr[i+1])
  }
  shock_end = EsArr_cnt; 
  EsArr_cnt = 0;
  shock_cnt = 0;
  shock_arr = 0;
  ShockTimer.deleteTimer(ShockTimerId);
  ShockTimerId = ShockTimer.setInterval(ShockCountTime,ShockTimerFunc);
}

void ES_Start(){
  EsArr;
}