#line 1 "c:\\Github\\Geekble-Electric_Chair_sub\\ElectricChair_sub.h"
#ifndef _DONE_ELECTRIC_CHAIR_CODE_
#define _DONE_ELECTRIC_CHAIR_CODE_

#include "Library_and_pin.h"

//****************************************Serial SETUP****************************************
HardwareSerial subTTGO(1);

void Serial_HandShake();
void Serial_RestartCheck();
void Serial_Read();
void SerialSend(String data);

String last_recv;

//****************************************Wifi SETUP****************************************
HAS2_Wifi has2wifi;

void WifiInit();
void WifiCheckOTA();

bool IsWifiConnected = false;

//****************************************SimpleTimer SETUP****************************************
SimpleTimer BlinkTimer;
SimpleTimer BreatheTimer;
SimpleTimer RiseTimer;
SimpleTimer ShockTimer;
SimpleTimer EffectTimer;

void TimerInit();

void BlinkTimerStart(int Neo, int NeoColor);
void BlinkTimerFunc();
void BlinkTopTimerFunc();
void BlinkAllTimerFunc();
void BreatheTimerStart(int Neo, int NeoColor);
void BreatheTimerFunc();
void ShockTimerFunc();
void ShockArrTimerFunc();
void RiseTimerStart(int color_code, int time);
void RiseTimerFunc();
void EffectTimerStart(int color_code);
void EffectTimerFunc();


int BlinkTimerId;
int BreatheTimerId; 
int RiseTimerId;
int ShockTimerId;
int EffectTimerId;

// blink setup
unsigned long BlinkTime = 250;   // 0.25sec
int blink_num = 5;
int blink_time = 500;

int blink_neo = 0;
int blink_color = 0;
bool blink_on = true;

// shock setup
unsigned long ShockCountTime = 1000;     // 1sec
int shock_interval = 10;                 // ES 인터벌 간격(초)
int shock_cnt = 0;
int shock_arr = 0;
int shock_end = 0;

// breathe setup
int breathe_step = 0;
int breathe_step_max = 60;
unsigned long BreatheTime = 4 *1000/(breathe_step_max);    // n_sec

int breathe_neo = 0;
int breathe_color = 0;
int breathe_color_arr[3];
bool IsCountUP = true;

// Rise setup
int RiseStep = 50;
int RiseColor = 0;
int RiseCNT = 0;
long RiseTime = 15 *1000/RiseStep;    // initial setting

int MIDpoint = 154/2 - 10;
int STRpoint = MIDpoint-RiseStep;
int ENDpoint = MIDpoint+RiseStep;

// Effect setup
unsigned long EffectTime = 80;

int EffPoint = 0;
int EffColor = 0;

//****************************************Light Control SETUP****************************************
void NeopixelInit();
void AllNeoColor(int color_code);

const int NeoNum = 3;
const int NumPixels[3] = {84,12,155};

enum {TOP = 0, TAG, BOT, TOPTAG, ALLNEO};   // led_code
Adafruit_NeoPixel pixels[3] = {Adafruit_NeoPixel(NumPixels[TOP], NEO_TOP, NEO_GRB + NEO_KHZ800),
                               Adafruit_NeoPixel(NumPixels[TAG], NEO_TAG, NEO_GRB + NEO_KHZ800),
                               Adafruit_NeoPixel(NumPixels[BOT], NEO_BOT, NEO_GRB + NEO_KHZ800)};

enum {WHITE = 0, RED, YELLOW, GREEN, BLUE, PURPLE, BLACK, BLUE0, BLUE1, BLUE2, BLUE3};     // Neopixel 색상정보
int color[11][3] = {  {180, 180, 180},   //WHITE
                      {180, 0, 0},     //RED
                      {180, 180, 0},    //YELLOW
                      {0, 180, 0},     //GREEN
                      {0, 0, 180},     //BLUE
                      {180, 0, 180},    //PURPLE 
                      {0, 0, 0},      //BLACK
                      {0, 0, 20},     //ENCODERBLUE0
                      {0, 0, 40},     //ENCODERBLUE1
                      {0, 0, 60},     //ENCODERBLUE2
                      {0, 0, 80}};    //ENCODERBLUE3

enum {STATIC = 0, BREATHE, RISE, BLINK = 10};
void LightControl(int color_code, int led_mode, int tag_mode, int bot_mode);
void LightMode(int light_code, int color_code, int mode);

//****************************************Electric Shock SETUP****************************************
void EsInit();
void EsOn(bool tf);
void ES_Stage(int stage);
void ES_Info(int start_point, int end_point);
void ES_Loop_Confirm(int loop_num);
void ES_Print();
void ES_Start(int sec, int strength);

int EsStage = 0;
int curr_EsStage = 0;
int EsArr[60] = {0};
int EsArr_max = 60;
int EsArr_cnt = 0;
bool IsEsHigh = false;

int ShockLevel_max = 255;      // max 255
int ShockLevel = 0;

//****************************************DFPlayer SETUP****************************************
HardwareSerial serialDFP(2);
DFRobotDFPlayerMini DFPlayer;

void DfpInit();

#endif