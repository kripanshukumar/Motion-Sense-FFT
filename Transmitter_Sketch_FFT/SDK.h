//=======================================================================================//

void takeReading() {                                         // One of the primary functions to run everything
  myFile = SD.open(FileName, FILE_WRITE);                    // Open the file to start the recording
  if (myFile) {                                              // If the file is opened successfully
    Serial.println("File opened successfully");              // Serial Print the status of file opening
    myFile.println("LOG starts here");                       // Start the recording with this string as first line
  }
  else {                                                     // If accessing the file failed then
    Serial.println("Failed to open the file");               // Serial Print the status
  }
  secondsTimer = millis();                                   // Primary timer which checks the 4 second loop time

  while (1) {                                                // Infinite loop which breaks only if certain conditions are met
    localiteration = iteration - prevIteration;              // This variable keeps the track the local or live iteration of the current 4 second loop
    
    if ((localiteration >= 512) && ((millis() - secondsTimer) >= 3500)) {   // The condition to break the loop: If the toal no of iterations is more 
                                                                            // than or equal to 512 and its been more than 3.5 seconds since the loop started
      
      prevIteration = iteration;                             // Reset the iteration tracker for the current loop
      break;                                                 // Come out of the infinite loop
    }
    iteration++;                                             // Increase the iteration number every loop
    sendIndex++;                                             // As we send one reading per 4 so we need to keep track of the send index. This helps in sending the payload according to our required rate.
    getReadings();                                           // Get readings, prepare the payload and store ths values in SD card
    if (sendIndex == 4) {                                    // If send index is 4 then:
      sendPayload();                                         // Send the payload using NRF transmitter
      sendIndex = 0;                                         // Reset the Index to again track which reading to send in order to maintain the 128hz rate
    }
    while ((micros() - loopTimer) <= ONE_SAMPLE_DURATION) {  // To make every reading equally spaced in time we use this while loop which makes processor wait preciesly if the above written code is execute well ahead in time.
      loopduration = micros() - loopTimer;                   // Calculate the duation of one loop of 512 iterations
    }
    tempavglooptime += loopduration;                         // Add all loopduration which we will later use to find the avg loop time of one reading
    loopTimer = micros();                                    // Set the loopTimer variable 
  } 
  avgx = sumx / 512;                                         // Calculate the AVG value of acceleration in x to later deduct it from live readings
  avgy = sumy / 512;                                         // Calculate the AVG value of acceleration in y to later deduct it from live readings
  avgz = sumz / 512;                                         // Calculate the AVG value of acceleration in z to later deduct it from live readings
  sumx = 0;                                                  // Reset the sumx accumulator
  sumy = 0;                                                  // Reset the sumx accumulator
  sumz = 0;                                                  // Reset the sumx accumulator
  avglooptime = tempavglooptime / 512;                       // Calculate the average time for one loop
  tempavglooptime = 0;                                       // Reset the loop time accumulator
  myFile.close();                                            // Close the File to save the data to SD card
  timer = millis() - secondsTimer;
  computeFFT();
  Serial.print(avgx); Serial.print(' ');                                             //
  Serial.print(avgy); Serial.print(' ');                                             // 
  Serial.print(avgz); Serial.print(' ');                                             // Dump Useful data to 
  Serial.print("Loop Completed in: "); Serial.println(timer);      // Serial monitor
  Serial.print(" Avergae loop time: "); Serial.print(avglooptime);                   //
  Serial.print(" Total no of Iterations: "); Serial.println(iteration);              //
}

//=======================================================================================//
