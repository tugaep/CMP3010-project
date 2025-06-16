# Smart Home Notification System – CMP3010 Embedded Systems Programming Term Project

## Overview

This Arduino-based **Smart Home Notification System** monitors various environmental and device states in your home using sensors and sends data to a connected ESP module for real-time mobile monitoring.

The system detects:
- Motion
- Water level
- Gas leaks
- Fridge door status
- Button press (used like a doorbell)

All sensor data is formatted as JSON and transmitted to the ESP module every 2 seconds, enabling real-time updates in a connected mobile app.

---

## Components Required

- Arduino UNO  
- ESP8266 (for Wi-Fi communication)  
- PIR Motion Sensor  
- Water Level Sensor  
- Gas Sensor   
- Reed Switch  
- Push Button  
- Buzzer  
- Jumper Wires  
- Breadboard  

---

## Pin Connections

| Component           | Arduino Pin       | Notes                              |
|---------------------|--------------------|-------------------------------------|
| Button              | D3                 | With internal pull-up               |
| Buzzer              | D8                 | Sound output                        |
| PIR Motion Sensor   | D2                 | Motion detection                    |
| Water Sensor        | A0                 | Analog input                        |
| Reed Switch         | A3                 | Used as digital with pull-up        |
| Gas Sensor          | A5                 | Analog input                        |
| ESP8266/ESP32       | D10 (RX), D11 (TX) | Via SoftwareSerial                  |

---

## Software Dependencies

- `SoftwareSerial` (Included in Arduino IDE)  
- `ArduinoJson` (Install via Arduino Library Manager)

---

## How It Works

1. **Sensor Monitoring**: Continuously reads motion, gas, water level, and door state.
2. **Button/Buzzer**: Pressing the button triggers the buzzer like a doorbell.
3. **Data Transmission**: Sensor readings are encoded as JSON and sent to the ESP every 2 seconds.
4. **Mobile App Ready**: The ESP code can be modified to push data to a mobile or web app.

---

## Setup Instructions

1. Install required libraries via the **Arduino Library Manager**.
2. Connect all components as per the [Pin Connections](#-pin-connections) table.
3. Upload the Arduino sketch to your board.
4. Flash your ESP module with the corresponding code and update your Wi-Fi credentials.
5. Verify communication and monitor sensor data via your app/backend.

---

## Usage

Once deployed, the system will:

✅ Sound the buzzer when the button is pressed  
✅ Detect motion in its range  
✅ Monitor water levels (e.g., flood detection)  
✅ Detect gas leaks for safety alerts  
✅ Monitor refrigerator door status  
✅ Transmit real-time updates via ESP to your app/backend

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Contact

For questions, improvements, or contributions:

**Tuğrap Efe Dikpınar**  
[tugaep@gmail.com](mailto:tugaep@gmail.com)
