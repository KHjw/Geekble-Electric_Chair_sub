void DfpInit(){
  DFPINIT:
  LightControl(YELLOW, STATIC, STATIC, STATIC);
  serialDFP.begin(9600, SERIAL_8N1, DFP_RX, DFP_TX);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if(!DFPlayer.begin(serialDFP)){
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    delay(500);
    goto DFPINIT;
  }
  Serial.println(F("DFPlayer Mini online."));

  DFPlayer.volume(20);              // max 30
  DFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  DFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}