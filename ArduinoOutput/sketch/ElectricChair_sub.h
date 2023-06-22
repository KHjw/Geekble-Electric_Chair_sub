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
void ShockTimerFunc();
void RiseTimerStart(int color_code, int time);
void RiseTimerFunc();


int BlinkTimerId;
int BreatheTimerId; 
int RiseTimerId;
int ShockTimerId;
int EffectTimerId;

// blink setup
unsigned long BlinkTime = 250;   // 1sec
int blink_num = 5;
int blink_time = 500;

int blink_neo = 0;
int blink_color = 0;
bool blink_on = true;

// shock setup
unsigned long ShockCountTime = 1000;    // 2sec
int shock_interval = 5;                 // ES 인터벌 간격(초)
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
int RiseStep = 100;
int RiseColor = 0;
int RiseCNT;
long RiseTime = 5 *1000/RiseStep;    // initial setting

int STRpoint = 5;
int ENDpoint = 140;
int MIDpoint = (ENDpoint - STRpoint)/2;

// Effect setup
unsigned long EffectTime = 100;

int EffPoint = 0;
int EffColor = 0;
int EffColorArr[3] = {0};

//****************************************Light Control SETUP****************************************
void NeopixelInit();
void AllNeoColor(int color_code);

const int NeoNum = 3;
const int NumPixels[3] = {84,12,154};

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

void ES_Stage(int stage);
void ES_Control(int start_point, int end_point);
void ES_Loop_Confirm(int loop_num);
void ES_Print();

int EsStage = 0;
int curr_EsStage = 0;
int EsArr[60] = {0};
int EsArr_max = 60;
int EsArr_cnt = 0;
bool IsEsOn = false;
bool IsEsStageChange = false;

//****************************************DFPlayer SETUP****************************************
HardwareSerial serialDFP(2);
DFRobotDFPlayerMini DFPlayer;

void DfpInit();

#endif