//====================================LIBS/HEADERS=======================================//

#include "Variables.h"                      // Stores all the variables
#include "RTC.h"                            // ALL RTC related Functions
#include "MPU.h"                            // All motion related functions
#include "NRF.h"                            // All Radio Communication functions
#include "FFT.h"
#include "SDK.h"                            // All timing functions and task scheduler
#include "STORAGE.h"                        // Functions related to SD card read and writes


//=====================================FUNCTIONS=========================================//

void setup() {
  Serial.begin(115200);                       //Initialize Serial Communication
  delay(100);                                 //Give some time to eastablish connection

  initMPU6050();                              // Initialize communication with Motion Processing Unit
  initRTC();                                  // Initialize Real Time Clock
  initStorage();                              // Connect with SD card
  initNRF();                                  // Initialize the RF module
  initFFT();
}

//=======================================================================================//

void loop() {

  takeReading();                              // Run this functions to take readings, store them on card, and transmit them.

}

//=======================================================================================//
