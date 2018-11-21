# Solar powered Weather Station
## Idea
Building a weather station that sends temperature, humidity and airpressure via MQTT to a server via WLAn connection while powered only by a solar panel and a 18650 Accu for long term operation without need of recharge.
## Components
- NodeMCU v3
- BME280 Sensor
- TP4056 charger module
- 5V solar panel
- 1N5817 diode
- 18650 Accu + Battery holder
- Resistor 200k

## Schematics
The solat panel is connected to the charger module inputs with the diode to protect reverse current through the solar panel during dark hours. The Accu is connected to the battery pins of the charger module. The output pins of the charger module are connected to the Vin and GND connectors of the nodemcu.
Pin D0 is shortened with RST to enable the deepsleep functionality.
Pin D1, D2 are used to connect SCL and SDA of the BME280 module.
Pin D3 is used to provide power for the BME module and is only activated when needed.
Pin A0 is connected with 200k against VIN (currently not in the pictures) to measure battery level. Code needs to be adapted to actual values. Code constant (5.03148F) calculates by measuring all resistors (the one placed - R1, and the ones on the board between A0 and ADC pin on the ESP - R2 - as well as between GND and the ADC pin of the ESP - R3) and calculate:
(R1+R2+R3)/R3
If thats not measuring exact enough you can divide the actual Vin by the measured value from ESP and multiply your current value with it. So when your resistor calculation results in 5.123, your ESP measures 4.0 but actually your battery has 4.2 your new factor will be:
5.123 * 4.2 / 4.0

![Breadboard](/images/breadboard.PNG)

## Code
Please rename the config.cpp.template to config.cpp and set your coresponding credentials and parameters.
The calculation for the battery level needs to be adapted for actual resistor values.

## Images
![Prototype](/images/prototype.jpg)

![18650+Charger](/images/18650+charger.jpg)

![wireing](/images/wireing.jpg)
