# Description:
The "Motion Sense FFT" project, based on Arduino and Raspberry Pi, offers real-time data gathering, logging, and wireless transmission of sensor readings. It integrates an MPU6050 sensor for measuring accelerometer and gyroscope data, a Real-Time Clock (RTC) module for accurate timestamping, and an SD card module for data storage. The nRF24L01 radio modem is employed for wireless communication between the sensor node and the receiver. After receiving data from multiple Arduino nodes, the Raspberry Pi handles post-processing and checks for concurrence before uploading the data to Thingspeak for visual analysis.

# Features:
1. Sensor Data Collection: The system is equipped with an MPU6050 sensor that captures tri-axial
accelerometer and gyroscope data. The sensor readings are collected at a high frequency of 128Hz,
ensuring accurate and real-time measurements.
2. Real-Time Clock (RTC): To maintain accurate timestamps for each data reading, the project integrates
an RTC module. The RTC provides precise timekeeping even when the Arduino is powered off.
3. SD Card Data Storage: All collected sensor data is logged and saved on an SD card. The data is
organized in a CSV-like format, including the iteration number, timestamp, and tri-axial accelerometer
readings.
4. Wireless Data Transmission: The wireless communication is established using the nRF24L01 radio
modem. The sensor node sends data packets wirelessly to a designated receiver node.
5. Fast Fourier Transform (FFT): The system also features an FFT library, allowing users to perform
frequency analysis on the collected sensor data if required.

# Components Used:
ATMEGA328P 8-bit AVR CPU running at a maximum clock speed of 20 MHz.
MPU6050 Inertial Measurement Unit
RTC Module Provides accurate timekeeping, even when the Arduino is powered off.
SD Card Module An interface to read and write data to an SD card for data storage.
nRF24L01 Radio Modem wireless communication module operating at 2.4Ghz

# Operation:
1. Sensor Initialization:
* The project starts by initializing the MPU6050 sensor, which is connected to the Arduino board via the
I2C bus.
 The sensor is configured to provide accelerometer and gyroscope readings with a resolution of 16 bits,
allowing for precise measurements.
2. Real-Time Clock Setup:
* The Real-Time Clock (RTC) module is initialized to maintain accurate timekeeping. It ensures that each
data reading is timestamped correctly, even when the Arduino is powered off.
3. SD Card Initialization and File Creation:
* The SD card module is initialized to establish communication with the SD card.
* At the beginning of each data logging session, a new file is created on the SD card to store the sensor data. The filename is generated based on the current date and time.
4. Data Collection and Payload Preparation:
* The main loop of the program begins data collection from the MPU6050 sensor.
* At a high frequency of 128Hz, the Arduino reads the tri-axial accelerometer and gyroscope values from
the MPU6050 sensor.
* The RTC module is used to get the current date and time for timestamping the readings.
* The readings, iteration number, and timestamp are combined to create a payload for transmission and
data storage.
* Additionally, the average acceleration values (avgx, avgy, avgz) are calculated from the 512 collected
readings to be deducted from live readings.
5. Wireless Data Transmission:
* The nRF24L01 radio modem is configured to establish wireless communication between the sensor node
and a designated receiver node.
* The payload, containing the iteration number, timestamp, and sensor readings, is sent wirelessly to the receiver node at a specific data rate (250kbps) and channel (90).
6. Data Logging to SD Card:
* The payload data is also written to the SD card file. Each line in the file contains the iteration number, timestamp, and tri-axial accelerometer readings in CSV-like format.
* This allows the data to be stored on the SD card for further analysis or long-term monitoring.
7. Loop Timing and Averaging:
* To maintain a consistent data collection rate, a loop timer is used to ensure a fixed duration
(ONE_SAMPLE_DURATION) between each iteration.
* The average loop time is calculated to track the time taken for each iteration and maintain the desired data collection frequency.
8. FFT (Optional):
* If required, the system can perform a Fast Fourier Transform (FFT) on the collected accelerometer data.
* The FFT library is used to compute the frequency components of the acceleration signal, enabling
frequency analysis.

# Learnings/ Skills gained:
* Sensor Integration: Learning how to interface and configure sensors like the MPU6050 via the I2C protocol, retrieving
raw data from the sensor, and converting it into meaningful values (acceleration and rotational velocity).
* Real-Time Clock (RTC) Usage: Understanding the communication protocol (I2C or SPI) with the RTC module, configuring timekeeping settings, and using library functions to set and retrieve time information accurately.
* Wireless Communication: Configuring the nRF24L01 radio module with the appropriate settings (data rate, channel), managing the read and write pipes, and handling packet transmission and reception.
* Data Logging and Storage: Understanding the SD card communication protocol (SPI), managing file handling (create, open, write, close), and organizing data in a CSV-like format with proper timestamps.
• Fast Fourier Transform (FFT): Implementing FFT algorithms to convert time-domain data (acceleration readings) into frequency-domain data, enabling frequency analysis for vibration or signal processing applications.
* Time Management: Planning the data collection loop timing to achieve the desired data sampling frequency (128Hz) using loop timers and microsecond calculations.

# Images:
<img src="https://github.com/kripanshukumar/Motion-Sense-FFT/blob/main/Images/Pasted%20File%20at%20August%201,%202021%2012_06%20AM.png" width=100% height=100%>
<img src="https://github.com/kripanshukumar/Motion-Sense-FFT/blob/main/Images/Pasted%20File%20at%20August%202,%202021%2012_04%20AM.png" width=100% height=100%>
