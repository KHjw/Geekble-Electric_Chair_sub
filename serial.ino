//****************************************Serial Communication****************************************
void Serial_HandShake(){
  Serial.println("Serial Handshake Init");
  subTTGO.begin(9600, SERIAL_8N1, SUBTTGO_RX_PIN, SUBTTGO_TX_PIN);
  RECONNECT_TTGO:
  delay(100);
  Serial.println("Connecting to TTGO");
  SerialSend("connect");
  if(subTTGO.available()){
    if(subTTGO.read() == '@'){
      String recv_data = subTTGO.readStringUntil(' ');
      if(recv_data == "connect"){
        Serial.println("recv CONNECT");
        SerialSend("ok");
        LightControl(BLUE, STATIC, STATIC, STATIC);
        goto RECONNECT_TTGO;
      }
      else if(recv_data == "ok"){
        Serial.println("TTGO CONNECTED");
        LightControl(PURPLE, STATIC, STATIC, STATIC);
      }
      else{
        Serial.println("connection ERROR");
        Serial.println("from main : " + recv_data);
        goto RECONNECT_TTGO;
      }
    }
    else goto RECONNECT_TTGO;
  }
}

void Serial_Read(){
  if(subTTGO.available()){
    if(subTTGO.read() == '@'){
      String recv_data = subTTGO.readStringUntil(' ');
      Serial.println("from main : " + recv_data);
      
      EsOn(false);
      DFPlayer.pause();
      RiseCNT = 0;
      RiseTimer.deleteTimer(RiseTimerId);
      ShockTimer.deleteTimer(ShockTimerId);
      
      if(recv_data == "connect"){
        SerialSend("ok");
      }
      else if(recv_data == "setting")         LightControl(WHITE,  STATIC, STATIC, STATIC);
      else if(recv_data == "ready")       		LightControl(RED,    STATIC, STATIC, BREATHE);
      else if(recv_data == "activate_wait")   LightControl(YELLOW, STATIC, STATIC, BREATHE);
      else if(recv_data == "activate_t1")		  LightControl(GREEN,  STATIC, STATIC, BREATHE);
      else if(recv_data == "activate_t2") 	  LightControl(GREEN,  BLINK,  BLINK,  BREATHE);
      else if(recv_data == "activate_t3") 	  LightControl(BLUE,	 STATIC, STATIC, BREATHE);
      else if(recv_data == "stage1"){
        LightControl(BLUE, STATIC, STATIC, BREATHE);
        EsStage = 1;
        Serial.println("curr_EsStage:" + (String)(curr_EsStage) + " / EsStage:" + (String)(EsStage));
        if(curr_EsStage != EsStage){
          DFPlayer.playLargeFolder(2,1);
        }
        else{
          ES_Start(10, 40);
          DFPlayer.start();
        }
      }
      else if(recv_data == "stage2"){
        LightControl(BLUE, STATIC, STATIC, BREATHE);
        EsStage = 2;
        Serial.println("curr_EsStage:" + (String)(curr_EsStage) + " / EsStage:" + (String)(EsStage));
        if(curr_EsStage != EsStage){
          DFPlayer.playLargeFolder(2,2);
        }
        else{
          ES_Start(5, 70);
          DFPlayer.start();
        }
      }
      else if(recv_data == "stage3"){
        LightControl(BLUE, STATIC, STATIC, BREATHE);
        EsStage = 3;
        Serial.println("curr_EsStage:" + (String)(curr_EsStage) + " / EsStage:" + (String)(EsStage));
        if(curr_EsStage != EsStage){
          DFPlayer.playLargeFolder(2,3);
        }
        else{
          ES_Start(5, 100);
          DFPlayer.start();
        }
      }
      else if(recv_data == "cool")
        LightControl(RED,    STATIC, STATIC, BREATHE);
      else if(recv_data == "rescue"){
        LightControl(GREEN, STATIC, BLINK, RISE);
        DFPlayer.start();
      }
      else if(recv_data == "rescue_suc"){
        AllNeoBlink(GREEN, 4, 500);
        LightControl(RED, STATIC, STATIC, BREATHE);
      }
      else if(recv_data == "rescue_fail"){
        DFPlayer.start();
        AllNeoBlink(RED, 5, 250);
      }
      else if(recv_data == "shock"){
        DFPlayer.start();
        Serial.println("Shock");
        if(EsStage == 1)          ES_Start(10, 40);
        else if(EsStage == 2)     ES_Start(5, 70);
        else if(EsStage == 3)     ES_Start(5, 100);
        curr_EsStage = EsStage;
      }
    }
    else
      Serial.println("[ERROR] : " + recv_data);
  }
}

void SerialSend(String data){
  String SendData = "@" + data + " ";
  subTTGO.print(SendData);
  Serial.println("to Main : " + SendData);
}
// Serial.println("curr_EsStage:" + (String)(curr_EsStage) + " / EsStage:" + (String)(EsStage));