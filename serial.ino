//****************************************Serial Communication****************************************
void SerialInit(){
}

void Serial_HandShake(){
  Serial.println("Serial Handshake Init");
  subTTGO.begin(9600, SERIAL_8N1, SUBTTGO_RX_PIN, SUBTTGO_TX_PIN);
  RECONNECT_TTGO:
  delay(100);
  Serial.println("Connecting to TTGO");
  subTTGO.print("connect ");
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil(' ');
    if(recv_data == "connect"){
      Serial.println("recv CONNECT");
      subTTGO.print("ok ");
      LightControl(BLUE, STATIC, STATIC, STATIC);
      goto RECONNECT_TTGO;
    }
    else if(recv_data == "ok"){
      Serial.println("TTGO CONNECTED");
      LightControl(PURPLE, STATIC, STATIC, STATIC);
    }
    else{
      Serial.println("from main : " + recv_data);
      Serial.println("connection failed");
      goto RECONNECT_TTGO;
    }
  }
  else goto RECONNECT_TTGO;
}

void Serial_RestartCheck(){
  Serial.print("0");
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil(' ');
    if(recv_data == "connect"){
      subTTGO.print("ok ");
      Serial.println("send CONNECT");
    }
    else 
      Serial.println("from main : " + recv_data);
  }
  delay(500);
}

void Serial_Read(){
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil(' ');
    Serial.println("from main : " + recv_data);
    if(recv_data == "connect"){
      subTTGO.print("ok ");
    }
    else if(recv_data == "setting")         LightControl(WHITE,  STATIC, STATIC, STATIC);
    else if(recv_data == "ready")       		LightControl(RED,    STATIC, STATIC, BREATHE);
    else if(recv_data == "activate_wait")   LightControl(YELLOW, STATIC, STATIC, BREATHE);
    else if(recv_data == "activate_t1")		 {LightControl(GREEN,  STATIC, STATIC, BREATHE);
                                            DFPlayer.playLargeFolder(1,1);}
    else if(recv_data == "activate_t2") 	 {LightControl(GREEN,  BLINK,  BLINK,  BREATHE);
                                            DFPlayer.playLargeFolder(1,1);}
    else if(recv_data == "activate_t3") 	 {LightControl(BLUE,	 STATIC, STATIC, BREATHE);
                                            DFPlayer.playLargeFolder(1,1);}
    else if(recv_data == "stage1")     		 {LightControl(BLUE,   STATIC, STATIC, BREATHE);
                                            ES_Stage(1);}
    else if(recv_data == "stage2")     		 {LightControl(BLUE,   STATIC, STATIC, BREATHE);
                                            ES_Stage(2);}
    else if(recv_data == "stage3")				 {LightControl(BLUE,   STATIC, STATIC, BREATHE);
                                            ES_Stage(3);}
    else if(recv_data == "cool")						LightControl(RED,    STATIC, STATIC, BREATHE);
    else if(recv_data == "rescue")					LightControl(GREEN,  STATIC, BLINK,  RISE);
    else if(recv_data == "rescue_suc")		 {AllNeoBlink(GREEN, 4, 500);
                                            LightControl(RED,    STATIC, STATIC, BREATHE);}
    else if(recv_data == "rescue_fail")		  AllNeoBlink(RED, 5, 250);
    else if(recv_data == "shock"){
      if(EsStage == 1)          DFPlayer.playLargeFolder(2, 1);
      else if(EsStage == 2)     DFPlayer.playLargeFolder(2, 2);
      else if(EsStage == 3)     DFPlayer.playLargeFolder(2, 3);
      else                      DFPlayer.pause();
    }

    else                                    Serial.println("from main : " + recv_data);
    last_recv = recv_data;
  }
}