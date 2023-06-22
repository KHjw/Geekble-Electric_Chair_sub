//****************************************ES SETUP****************************************
void EsInit(){
  Serial.println("EsInit");
  pinMode(ES_PIN, OUTPUT);
  EsOn(false);
}

void EsOn(bool tf){
  if(tf == true){
    Serial.println("Es On");
    digitalWrite(ES_PIN, HIGH);
    IsEsOn = true;
  }
  else{
    Serial.println("Es Off");
    digitalWrite(ES_PIN, LOW);
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
    ES_Loop_Confirm(4);
    break;
  case 2:
    ES_Control(2,6);
    ES_Control(7,8);
    ES_Loop_Confirm(4);
    break;
  case 3:
    ES_Control(2,6);
    ES_Control(7,8);
    ES_Control(9,10);
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

void ES_Control(int start_point, int end_point){    // ES 정보입력 (시점, 종점)
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
    ES_Control(EsArr[i]+loop_end, EsArr[i+1]+loop_end);
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