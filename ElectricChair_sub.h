#ifndef _DONE_ELECTRIC_CHAIR_CODE_
#define _DONE_ELECTRIC_CHAIR_CODE_

#include "Library_and_pin.h"

//****************************************Serial SETUP****************************************
HardwareSerial subTTGO(1);

void Serial_HandShake();
void Serial_RestartCheck();

String last_recv;
String last_send;

void SerialInit();
void Serial_Read();

//****************************************SimpleTimer SETUP****************************************
SimpleTimer BlinkTimer;
SimpleTimer ShockTimer;
SimpleTimer BreatheTimer;

void TimerInit();

void BlinkTimerStart(int Neo, int NeoColor);
void BlinkTimerFunc();
// void ShockTimerStart(int Neo, int NeoColor);
void ShockTimerFunc();
void ConnTimerFunc();

int BlinkTimerId;
int ShockTimerId;
int BreatheTimerId;

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

// breathe setup
int breathe_step = 0;
int breathe_step_max = 20;
unsigned long BreatheTime = 4 *1000/(breathe_step_max*2);    // n_sec

int breathe_neo = 0;
int breathe_color = 0;
int breathe_color_arr[3];
bool IsCountUP = true;

// connect setup
unsigned long ConnectTime = 1000;    // 1sec

//****************************************Light Control SETUP****************************************
void NeopixelInit();
void AllNeoColor(int color_code);
void NeoBlink(int neo_code, int color_code);

void LedInit();
void LedColor(int color_code);
void LedBlink(int color_code);


const int NeoNum = 2;
const int NumPixels[2] = {12,12};

enum {TAG = 0, BOT, LED, LEDTAG,ALLNEO};   // led_code
Adafruit_NeoPixel pixels[2] = {Adafruit_NeoPixel(NumPixels[TAG], NEO_TAG, NEO_GRB + NEO_KHZ800),
                               Adafruit_NeoPixel(NumPixels[BOT], NEO_BOT, NEO_GRB + NEO_KHZ800)};

enum {WHITE = 0, RED, YELLOW, GREEN, BLUE, PURPLE, BLACK, BLUE0, BLUE1, BLUE2, BLUE3};     // Neopixel 색상정보
int color[11][3] = {  {20, 20, 20},   //WHITE
                      {40, 0, 0},     //RED
                      {40, 40, 0},    //YELLOW
                      {0, 40, 0},     //GREEN
                      {0, 0, 40},     //BLUE
                      {40, 0, 40},    //PURPLE
                      {0, 0, 0},      //BLACK
                      {0, 0, 20},     //ENCODERBLUE0
                      {0, 0, 40},     //ENCODERBLUE1
                      {0, 0, 60},     //ENCODERBLUE2
                      {0, 0, 80}};    //ENCODERBLUE3

enum {STATIC = 0, BREATHE, RISE, BLINK = 7};
void LightControl(int color_code, int led_mode, int tag_mode, int bot_mode);
void LightMode(int light_code, int color_code, int mode);

//****************************************Electric Shock SETUP****************************************
void EsInit();
void ES_Stage(int stage);
void ES_Control(int start_point, int end_point);
void ES_Loop_Confirm(int loop_num);
void ES_Start();


int EsArr[20];
int EsArr_cnt = 0;

#endif