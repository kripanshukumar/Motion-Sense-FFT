//=======================================================================================//
void initNRF() {                                  // Initialize the NRF module
  radio.begin ();                                 // Begin the communication with NRF
  radio.stopListening ();                         // Stop listening to incoming
  radio.setDataRate(RF24_250KBPS);                // Set the data rate of the wireless transmission
  radio.setChannel(90);                           // Set the transmittion channel
  radio.openWritingPipe (0x7878787878LL);         // Open one of the pipeline for communication
}

//=======================================================================================//

void sendPayload() {
  
    radio.write(&lowerpayload, 29);            // Send the payload to receiver

}

//=======================================================================================//
