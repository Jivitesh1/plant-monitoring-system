# plant-monitoring-system
A plant monitoring system using an ESP-32 MCU which uses dht-11/22 temp & humidity sensor, soil moisture sensor, along with an OLED display to show information locally and has IoT function so to remotely control water pumps and set watering parameters.
The Sensor info is collected by the MCU and is processed to control a relay module which can then control any sized water pump for watering plants.
This system can be used in homes especially when one leaves for long vacations, this keeps the owner updated and provides manual control for watering the plants.

How It Works
The ESP32 continuously reads data from the sensors
Soil moisture is compared against a set threshold
If the soil is dry, the relay turns the pump ON
Once sufficient moisture is reached, the pump turns OFF
Live data is shown on the OLED display and updated in the Blynk app
Users can manually control the pump and monitor conditions remotely
Getting Started
Upload the provided code to your ESP32
Connect the components as per the defined pins in the code
Add your WiFi credentials and Blynk authentication token
Set up the Blynk dashboard with the required virtual pins
Power the system and verify sensor readings

You may need to calibrate the soil moisture sensor for accurate results.

Use Cases
Home gardening and indoor plants
Managing plants during travel or long absences
Small-scale greenhouse automation
Educational IoT and embedded systems projects
Notes
Soil moisture sensors require calibration for reliable readings
The DHT11 works but can be replaced with DHT22 for better accuracy
Ensure a stable power supply for consistent operation
