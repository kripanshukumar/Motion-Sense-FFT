//=======================================================================================//

void initMPU6050() {     
  Wire.begin();                                                                                          // Initialize the I2C communication

  Serial.println("Initializing MPU6050...");                                                             // initialize device
  mpu.initialize();                                                                                      // initialize device

  Serial.println("Testing device connections...");                                                       // verify connection
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");  // verify connection

}

//=======================================================================================//

void prepPayload(uint32_t value, int pos) {        // Function to convert the 32 bit value into array of 4 elements of 8bits.

  lowerpayload[9 + (pos * 4)] = value % 256;       // Writing the first register of array
  value = value / 256;
  lowerpayload[10 + (pos * 4)] = value % 256;      // Writing the second register of array
  value = value / 256;
  lowerpayload[11 + (pos * 4)] = value % 256;      // Writing the third register of array
  value = value / 256;
  lowerpayload[12 + (pos * 4)] = value % 256;      // Writing the fourth register of array
}

//=======================================================================================//

void getReadings() {                               // This function takes reading from MPU and prepares the payload which is to be transmitted wirelessly.
  tempitr = iteration;                             // Copy the iteration number to temporary varible to do operations on it.

  itr0 = tempitr % 256;                            // Calculating first register value
  tempitr = tempitr / 256;
  itr1 = tempitr % 256;                            // Calculating second register value
  tempitr = tempitr / 256;
  itr2 = tempitr % 256;                            // Calculating third register value
  tempitr = tempitr / 256;
  itr3 = tempitr % 256;                            // Calculating fourth register value
  lowerpayload[0] = itr0;                          // Writing to first register of payload array
  lowerpayload[1] = itr1;                          // Writing to second register of payload array
  lowerpayload[2] = itr2;                          // Writing to third register of payload array
  lowerpayload[3] = itr3;                          // Writing to fourth register of payload array

  rtc.getDateTime(&dateTime);                      // RTC function to gather current data and time information
  
  yr = dateTime.year;                              // Store the year value to variable
  mth =  dateTime.month;                           // Store the month value to mth variable
  dy =  dateTime.day;                              // Store the day value to dy variable
  hr =  dateTime.hour;                             // Store the current hour value to hr variable
  mn =  dateTime.minute;                           // Store the minute value to mn variable
  sec = dateTime.second;                           // Store the seconds value to sec variable
  lowerpayload[4] = mth;                           // Write the month data to payload array
  lowerpayload[5] = dy;                            // Write the day data to payload array
  lowerpayload[6] = hr;                            // Write the hour data to payload array
  lowerpayload[7] = mn;                            // Write the minute data to payload array
  lowerpayload[8] = sec;                           // Write the seconds data to payload array
 
  // Prepare timestamp string to further use in writing to SD card.
  timestamp =String(yr) + "/"+ String(mth) + "/" + String(dy) + "," + String(hr) + ":" + String(mn) + ":" + String(sec); 

  mpu.getAcceleration(&axRAW, &ayRAW, &azRAW);     // Ask for the data from MPU6050 module

  tempax = ((float)(axRAW ) / 16384);        // Temporary variable to store x- acceleration
  tempay = ((float)(ayRAW ) / 16384);        // Temporary variable to store y- acceleration
  tempaz = ((float)(azRAW ) / 16384);        // Temporary variable to store z- acceleration

  if (sendIndex == 4) {
  acc = tempax + tempay + tempaz;
  vReal[localiteration/4] = acc;
  vImag[localiteration/4] = 0.0;
  //Serial.print(localiteration);Serial.print('\t');Serial.println(vImag[localiteration]);
  }
  
  sumx += tempax;                            // Variable to store the sum of acceleration of x axis for 512 samples
  sumy += tempay;                            // Variable to store the sum of acceleration of y axis for 512 samples
  sumz += tempaz;                            // Variable to store the sum of acceleration of z axis for 512 samples

  prepPayload((ax[localiteration] - avgx) * 16384, 0);  // Write x values to the four 8bit register of payload array
  prepPayload((ay[localiteration] - avgy) * 16384, 1);  // Write y values to the four 8bit register of payload array
  prepPayload((az[localiteration] - avgz) * 16384, 2);  // Write z values to the four 8bit register of payload array
  lowerpayload[21] = this_node;                         // Write the current node value to the payload array
  lowerpayload[22] = yr%256;                            // Write the lower byte of the year to the payload array
  yr = yr/256;
  lowerpayload[23] = yr %256;                           // Write the higher byte of the year to the payload array
  
  // sub-string of the string which will be written to the sd card.
  byproduct = ',' + String(ax[localiteration]) + "," + String(ay[localiteration]) + "," + String(az[localiteration])+ "," + String(frequency) + "," + String(amplitude);

  // Local Iteration is nothing but the iteration number falling in the range of 1 to 512 of one loop of readings
  ax[localiteration] = tempax;                          // Storing the temporary value of ax in the 512 array
  ay[localiteration] = tempay;                          // Storing the temporary value of ay in the 512 array
  az[localiteration] = tempaz;                          // Storing the temporary value of az in the 512 array
  
  tempPayload = String(iteration) + "," + timestamp + byproduct; // Prepare the complete string to write to SD card
  myFile.println(tempPayload);                          // Send the string to the SD card.
}

//=======================================================================================//
