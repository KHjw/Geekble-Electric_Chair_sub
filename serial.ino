//****************************************Serial Communication****************************************
void SerialInit(){
}

void Serial_HandShake(){
  Serial.println("Serial Handshake Init");
  subTTGO.begin(9600, SERIAL_8N1, SUBTTGO_RX_PIN, SUBTTGO_TX_PIN);
  RECONNECT_TTGO:
  Serial.println("Connecting to TTGO");
  subTTGO.println("connect");
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil('\n');
    if(recv_data == "connect"){
      subTTGO.println("ok");
      goto RECONNECT_TTGO;
    }
    else if(recv_data == "ok"){
      Serial.println("TTGO CONNECTED");
    }
    else
      goto RECONNECT_TTGO;
  }
}

void Serial_RestartCheck(){
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil('\n');
    if(recv_data == "connect"){
      subTTGO.println("ok");
    }
  }
}

void Serial_Read(){
  if(subTTGO.available()){
    String recv_data = subTTGO.readStringUntil('\n');
    if(recv_data == "connect"){
      subTTGO.println("ok");
      LightControl(PURPLE, STATIC, STATIC, STATIC);
    }
    else    
      Serial_Control(recv_data);
    last_recv = recv_data;
  }
}

void Serial_Control(String recv_data){
  if(recv_data == "setting")              LightControl(WHITE,  STATIC, STATIC, STATIC);
  else if(recv_data == "ready")       		LightControl(RED,    STATIC, STATIC, BREATHE);
  else if(recv_data == "activate_wait")   LightControl(YELLOW, STATIC, STATIC, BREATHE);
  else if(recv_data == "activate_t1")		  LightControl(GREEN,  STATIC, STATIC, BREATHE);
  else if(recv_data == "activate_t2") 		LightControl(GREEN,  BLINK,  BLINK,  BREATHE);
  else if(recv_data == "activate_t3") 		LightControl(BLUE,	 STATIC, STATIC, BREATHE);
  else if(recv_data == "stage1")     		 {LightControl(BLUE,   STATIC, STATIC, BREATHE);
                                          ES_Stage(1);}
  else if(recv_data == "stage2")     		 {LightControl(BLUE,   STATIC, STATIC, BREATHE);
                                          ES_Stage(2);}
  else if(recv_data == "stage3")				 {LightControl(BLUE,   STATIC, STATIC, BREATHE);
                                          ES_Stage(3);}
  else if(recv_data == "cool")						LightControl(RED,    STATIC, STATIC, BREATHE);
  else if(recv_data == "rescue")					LightControl(GREEN,  STATIC, BLINK,  RISE);
  else if(recv_data == "rescue_suc")			LightControl(GREEN,  STATIC, STATIC, STATIC);
  else if(recv_data == "rescue_fail")		  LightControl(RED,    BLINK,  BLINK,  BLINK);
}