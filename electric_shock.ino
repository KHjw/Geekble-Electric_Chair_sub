//****************************************ES SETUP****************************************
void EsInit(){
  pinMode(ES_PIN, OUTPUT);
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

void ES_Control(int start_point, int end_point){
  EsArr[EsArr_cnt] = start_point;
  EsArr_cnt ++;
  EsArr[EsArr_cnt] = end_point;
  EsArr_cnt ++;
}

void ES_Loop_Confirm(int loop_num){
  EsArr_cnt = 0;
  shock_cnt = 0;
}

void ES_Start(){
  EsArr;
}