//=======================================Libraries=======================================//

#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Time.h>
#include <stdio.h>
#include <TimeLib.h>
#include <MPU6050.h>
#include <nRF24L01.h>             /* to handle this particular modem driver*/
#include <RF24.h>                 /* the library which helps us to control the radio modem*/
#include "arduinoFFT.h"
#include <Microduino_RTC.h>


//========================================Objects========================================//

MPU6050 mpu;
RTC rtc;
File myFile;
RF24 radio(9,10);  
arduinoFFT FFT = arduinoFFT();

//===================================Defined Variables===================================//

//year, month, weekday, day, hour, minute, second
DateTime dateTime = {2020, 4, 9, 24, 22, 58, 40};

#define chipSelect 7
#define calibrationSamples 30
#define ONE_SAMPLE_DURATION 7670

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

//=================================Undefined Variables===================================//

const uint16_t this_node = 01;       
const uint16_t other_node = 00;

uint8_t lowerpayload[32];

uint32_t loopTimer = 0, secondsTimer = 0, t = 0;
int loopduration = 0, avglooptime = 0;;
uint32_t tempavglooptime = 0;
uint32_t timer = 0;

String tempPayload ="";
String File_Name = "";
String timestamp = "";
String byproduct;
String FileName;

uint32_t itr0 = 0, itr1 = 0, itr2 = 0, itr3 = 0;
uint32_t prevIteration = 0;
uint32_t iteration = 0;
int localiteration = 0;
int sendIndex = 0;
uint32_t tempitr;

int yr = 0, mth = 0, dy = 0, hr = 0, mn = 0, sec = 0;

float tempax = 0, tempay = 0, tempaz = 0, acc = 0;
double sumx = 0, sumy = 0, sumz = 0; 
float avgx = 0, avgy =0, avgz = 0;
int16_t axRAW,ayRAW,azRAW;
float ax[512] = {0};
float ay[512] = {0};
float az[512] = {0};
//float az[129] = {0};


const uint16_t samples = 128;                               //This value MUST ALWAYS be a power of 2
//const double signalFrequency = 1000;
const double samplingFrequency = 32;
//const uint8_t amplitude = 100;

double vReal[samples];
double vImag[samples];

double frequency = 0, amplitude = 0;
uint32_t payloadFrequency = 0, payloadAmplitude = 0;

//=======================================================================================//
