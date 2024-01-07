#include <SPI.h>             /* to handle the communication interface with the modem*/
#include <nRF24L01.h>        /* to handle this particular modem driver*/
#include <RF24.h>            /* the library which helps us to control the radio modem*/
#define led_pin 3            /* Connect LED anode to D3 (PWM pin) */

RF24 radio(9, 10);           /* Creating instance 'radio'  ( CE , CSN )   CE -> D7 | CSN -> D8 */
const byte Address[6] = "00009"; /* Address from which data to be received */


uint32_t incoming = 0;
int commaIndexes[4] = {0, 0, 0, 0};
int index = 0;
String ax = "     ", ay = "     ", az = "    ";
String accelerationString;
uint32_t iteration = 0;
uint32_t t = 0;
String payload = "                         ";
uint32_t itr[30] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0
                   };
int32_t x = 0, y = 0, z = 0;
int32_t frequency = 0, amplitude = 0;
float DCxyz = 0;
int nodeID = 0;
int yr = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);            /*Setting baudrate of Serial Port to 9600*/
  radio.begin();                   /* Activate the modem*/
  radio.stopListening();
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(90);
  radio.openReadingPipe(1, 0x7878787878LL); /* Sets the address of receiver from which program will receive the data*/
  Serial.print("Initializing the Receiver.......");
  Serial.println();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  incoming = 0;
  t = millis();

  radio.startListening();          /*Setting modem in Receiver mode*/
  if (radio.available())
  {
    while ((millis() - t) <= 4000) {
      while (radio.available())              /* Loop until receiving valid data*/
      {
        uint8_t temp[32] = {0};
        radio.read(&temp, sizeof(temp));//Serial.print(payload);
        for (int j = 0; j <= 29; j++) {
          itr[j] = temp[j];
        }
        nodeID = temp[21];
        amplitude = itr[24] + (itr[25]*256) + (itr[26]*65536);
        frequency = itr[27] + (itr[28]*256) + (itr[29]*65536);
        iteration = itr[0] + (itr[1] * 256) + (itr[2] * 65536) + (itr[3] * 16777216);
        yr = itr[22] + (itr[23] * 256);
        payload = String(nodeID) + ',' + String(iteration) + ',' + String(yr) + '/' + String(itr[4]) + '/' + String(itr[5]) + ',' + String(itr[6]) + ':' + String(itr[7]) + ':' + String(itr[8]) + ',';
        Serial.print(payload);
        storXYZ();
        Serial.println("    " + String(amplitude)+','+String(frequency));
        // Serial.println();
        incoming++;
      }

    }
    //Serial.print("ITERATIONS = : "); Serial.println(incoming);
  }


}


void storXYZ() {

  x = itr[9] + (itr[10] * 256) + (itr[11] * 256 * 256) + (itr[12] * 256 * 256 * 256);

  y = itr[13] + (itr[14] * 256) + (itr[15] * 256 * 256) + (itr[16] * 256 * 256 * 256);

  z = itr[17] + (itr[18] * 256) + (itr[19] * 256 * 256) + (itr[20] * 256 * 256 * 256);
  DCxyz = ((float)x / 16384) + ((float)y / 16384) + ((float)z / 16384);
  Serial.print(DCxyz, 4);Serial.print(',');
  //  Serial.print((float)x / 16384);
  //  Serial.print(", "); Serial.print((float)y / 16384);
  //  Serial.print(", "); Serial.print((float)z / 16384);
}
