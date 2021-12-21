# Greenhouse-simulation
This Arduino UNO code implements a greenhouse irrigation system using DHT11 and soil moisture sensors.

Overview
---
Scarcity of water is one of the major problems in the current development of the agriculture sector and due to increase in jobs in cities there is less labor for the management of crops. The proposed system provides improvement in agriculture by using automation and modernization of traditional agricultural systems. The solution proposed is a smart irrigation system which can control and regulate water usage with the help of less labor. The features of this system are monitoring of humidity, soil moisture, and temperature through DHT sensors. The data is tracked in real time through the sensors, Xbee modules and Arduino Uno.


How it works:
---
This project is based on realizing IoT based greenhouse farming where the temperature, humidity and soil moisture is monitored to help the crops/plants grow in an ideal environment. DHT11 sensor is used to monitor temperature and humidity. A DC operated fan is used to bring the temperature of the surroundings to a desired value and soil moisture is used to balance the moisture content in the soil using a motor pump. Arduino UNO acts as the processing unit to collect the sensor output and to control the conditions. The data from the Arduino is presented on the LCD display.  For remote reception of data and to realize IoT we have interfaced a Xbee module both in the transmitting and receiving side. Through the Xbee module, relevant status of the farm’s environment is monitored. Finally, an RTC timer circuit is connected to Arduino UNO to get the time.

<img alt="Greenhouse" src="https://user-images.githubusercontent.com/85611307/146880937-ec4224b5-16b7-4da4-8e68-9328028b4564.png">


Algorithm:
---
**Step 1**: Start

**Step 2**: humidity and temperature values are sensed by the DHT11 sensor. Soil moisture sensor senses the moisture content of
the soil.

**Step 3**: If soil moisture value is above the threshold value (>30%) then the motor pump will continue to be in OFF state. If the
temperature of the surroundings is below the threshold value (<28 °C) DC fan will continue to be in OFF state.

**Step 4**: If soil moisture value is below the threshold value (<30%) then the motor pump will switch to ON state automatically. If
the temperature of the surroundings is above the threshold value (>28 °C) DC fan will switch to ON state automatically.

**Step 5**: Once moisture level and temperature level become equal to the threshold value (>70% and <22 °C) then both motor
pump and DC motor will switch back to OFF state.

**Step 6**: If the humidity of the surroundings is greater than 60%, then it is treated as a humid condition and the motor switches to
OFF state for soil moisture level greater than 50%.

**Step 7**: End

