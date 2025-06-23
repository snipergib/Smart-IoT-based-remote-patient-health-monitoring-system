# Smart IoT-based Remote Patient Health Monitoring System

## Project Overview

This IoT-enabled system continuously tracks a bedridden patient’s vital signs (ECG waveform, heart rate, and body temperature) from anywhere in the world.  By combining a microcontroller (Arduino) with a single-board computer (Raspberry Pi) and medical sensors, it streams patient data over the Internet for real-time remote monitoring.  Such a system enables caregivers to check a patient’s health anytime, potentially improving outcomes by early detection of anomalies.  In our design, sensor readings are processed by the Arduino and forwarded via the Raspberry Pi to a web or mobile dashboard, allowing clinicians or family members to view the patient’s vital signs live.

## Features

* **Real-time monitoring of multiple vitals:** Continuously measures ECG (heart electrical activity), pulse (heart rate), and body temperature.
* **Remote access:** Data is transmitted over Wi-Fi/Internet so health data can be viewed from anywhere.
* **Alerts (optional):** The system can trigger alerts if any vital sign goes outside normal ranges (configurable thresholds).
* **Web/Mobile dashboard:** Provides a graphical interface for visualizing the live ECG waveform, heart rate (BPM), and temperature.
* **Portable and low-cost:** Uses inexpensive, off-the-shelf sensors (e.g. AD8232, Pulse Sensor, DS18B20) and boards (Arduino, Raspberry Pi).

## Technologies and Components Used

&#x20;*Figure: ECG sensor (AD8232 module) mounted on electrodes.* The **AD8232 ECG module** (Analog Devices AD8232 chip) is used for cardiac signal acquisition. The AD8232 is “an integrated front end for signal conditioning of cardiac bioelectric signals for heart rate monitoring”. It attaches to the patient via three electrodes (RA, LA, RL) and outputs an amplified ECG waveform on one analog pin. This module extracts and filters the weak heart electrical signal to produce a clear ECG trace. The Arduino reads the AD8232’s analog output (via an analog input pin) to capture the patient’s ECG waveform.

&#x20;*Figure: Pulse Sensor Amped for heart-rate (made by WorldFamousElectronics). The cable and strap allow clipping to a finger or earlobe.* The **Pulse Sensor Amped** is used to detect the patient’s pulse rate. It is a “plug-and-play heart-rate sensor for Arduino” that includes amplification and noise cancellation circuitry.  This sensor is attached to the patient’s fingertip or earlobe (using the provided clip or strap) and outputs an analog signal for each heartbeat. The Arduino samples this signal and computes the beats-per-minute (BPM) in real time.

&#x20;*Figure: Waterproof DS18B20 digital temperature sensor.* A **DS18B20 1-Wire temperature probe** is used for body-temperature monitoring. This digital sensor provides temperature readings with ±0.5°C accuracy and communicates over a single data line. It is powered from 3.3 V (from Arduino/RPi) and uses a 4.7 kΩ pull-up resistor on the data line. The microcontroller reads the DS18B20 via a OneWire interface to obtain the patient’s current temperature. Unlike analog thermistors, the DS18B20 outputs a digital value, making it well-suited for accurate IoT measurements over a wire.

* **Arduino microcontroller (e.g. Uno/Nano):** Reads sensor outputs (AD8232 ECG output, Pulse Sensor analog output) via its ADC channels and queries the DS18B20 (via a OneWire digital pin).
* **Raspberry Pi (e.g. Pi 3/4):** Acts as the gateway/server. It receives data from the Arduino (e.g. via USB-serial or GPIO), runs the IoT software (Python script or web server), and connects to Wi-Fi to upload data or serve a web dashboard.
* **Connectivity:** Wi-Fi or Ethernet on the Raspberry Pi provides Internet connectivity so that data can be accessed remotely.
* **Libraries/Software:** The Arduino uses libraries such as **PulseSensorPlayground** (for pulse detection), **OneWire** and **DallasTemperature** (for DS18B20), and standard analogRead functions. The Pi runs a Python or Node.js application to collect data and interface with the cloud or frontend.

## Hardware Setup Instructions

1. **Connect the ECG (AD8232) module:** Mount the disposable electrodes on the patient’s body (e.g. chest and leg as per standard 3-lead ECG placement). Plug the electrodes’ cables into the AD8232 module’s RA (white), LA (black), and RL (red) leads. Wire the AD8232 board to the Arduino: connect **AD8232 3.3V** to Arduino 3.3V, **AD8232 GND** to Arduino GND, **AD8232 OUTPUT** to an Arduino analog input (e.g. A1), and tie **LO+ / LO- pins to Arduino digital pins** (or simply leave LO+/LO– open if unused).
2. **Connect the pulse sensor:** Plug the Pulse Sensor Amped into the Arduino. It typically has three wires (VCC, GND, and Signal). Attach VCC to 5 V, GND to ground, and the SIGNAL pin to another analog input on the Arduino (e.g. A0). Secure the pulse sensor probe on the patient’s finger or earlobe (usually it has a clip or strap).
3. **Connect the temperature sensor:** Wire the DS18B20 with a 4.7 kΩ pull-up resistor between its data line and 3.3 V (or 5 V) as per the datasheet. Connect the data line to a digital GPIO pin on the Arduino (or to the Pi’s GPIO if reading directly), and power/GND accordingly.
4. **Arduino–Raspberry Pi interface:** Connect the Arduino to the Raspberry Pi via a USB cable (or via serial pins). The Arduino will send the processed sensor data (ECG level, pulse/BPM, and temperature) to the Pi.
5. **Power and network:** Power the Arduino and Pi (e.g. via separate power supplies or a shared USB power bank). Ensure the Raspberry Pi is connected to the Internet (via Wi-Fi or Ethernet).

## Software Setup Instructions

1. **Arduino side:** Install the Arduino IDE on a PC. In the IDE, install the **PulseSensor Playground** library (for pulse detection) and the **OneWire**/**DallasTemperature** libraries (for DS18B20). Load the provided Arduino sketch (e.g. `health_monitor.ino`), which reads the sensors and sends data over Serial. Verify the correct board/port and upload the sketch to the Arduino.
2. **Raspberry Pi side:** Boot the Raspbian (or similar) OS on the Pi. Enable any required interfaces (e.g. 1-Wire GPIO if reading DS18B20 directly). Install necessary Python packages (such as `pyserial` to read Arduino data, `RPi.GPIO`, and any web framework if used). Copy the Pi application script (e.g. a Python program) to the Pi.
3. **Network config:** Configure the Pi’s network (e.g. set up Wi-Fi SSID/password or Ethernet). Ensure the Pi can connect to the Internet and has permission to open any required ports.
4. **Running the system:** Launch the Arduino sketch (already auto-running after power-up) and start the Pi program (e.g. `python3 monitor_server.py`). The Pi program will read incoming sensor values from the Arduino and then process/store them. It may serve a web page or push data to a cloud service.

## Usage Example

After setup, power on the Raspberry Pi and Arduino. The Arduino immediately begins sampling sensor data. The pulse sensor’s LED should blink with the patient’s heartbeat, and the ECG module outputs a waveform correlated to the heart. On the Pi side, start the monitoring application. For example, if a web dashboard is provided, open a browser on a smartphone or PC and navigate to the Pi’s IP address. You should see live plots of the ECG waveform, the current BPM, and the patient’s temperature. Sample outputs may look like one would see on a simple ICU monitor – e.g. a real-time ECG trace and numeric readouts for heart rate and temperature. (See the code’s README comments for precise example commands or endpoints.)

## Contribution Guidelines

Contributions are welcome! To contribute, fork the repository and submit pull requests.  Please follow these guidelines:

* Document any new hardware or software you add.
* Before submitting, test your changes fully and ensure they do not break existing functionality.
* For major new features or changes, open an issue to discuss before coding.
