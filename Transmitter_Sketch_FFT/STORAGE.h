//=======================================================================================//

void createFile() {                                      // Function to create the file at the begning of startup of the module
  rtc.getDateTime(&dateTime);                            // Gather the Real Time Date and Time

  File_Name = String(dateTime.day) + String(dateTime.hour) + String(dateTime.minute) + String(dateTime.second) + ".txt";
  FileName = File_Name;                                  // Store the generated file name

  Serial.println(FileName);                              // Dump filename to serial port

  myFile = SD.open(FileName, O_CREAT);                   // Open the file just for removing the initial time consumption on writing first 
  delay(100);                                            // Small delay of 100 milliseconds
  myFile.close();
}

//=======================================================================================//

void initStorage() {                                     // Initialize the SD card communication
  if (!SD.begin(chipSelect)) {                           // Establize the connection with SD card
    Serial.println("Card failed, or not present");       // Dump details to Serial port if no card found
    // don't do anything more:
    return;                                             
  }
  Serial.println("card initialized.");                   // If card found dump this information
  delay(100);                                            // Small delay of 100 milli seconds
  createFile();                                          // Create File at the beging to avoid any delay while taking the readings.
}

//=======================================================================================//

void dumpFileToSerial() {                                // Dump SD card details to Serial port
  Serial.println("Trying to open the file: " + String(FileName));
  myFile = SD.open(FileName);                            // Open the file to gather the data
  if (myFile) {
    while (myFile.available()) {                         // If file is present and data is there then run this loop
      Serial.println(myFile.readStringUntil('\n'));      // Dump all the data to the serial port.
    }
    myFile.close();                                      // Close the File after data fetch is complete
  }
  else {                                                 // if the file didn't open, print an error:
    Serial.println("error opening " + String(FileName));
  }
}

//=======================================================================================//
