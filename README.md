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

## Schematics
The solat panel is connected to the charger module inputs with the diode to protect reverse current through the solar panel during dark hours. The Accu is connected to the battery pins of the charger module. The output pins of the charger module are connected to the Vin and GND connectors of the nodemcu.
Pin D0 is shortened with RST to enable the deepsleep functionality.
Pin D1, D2 are used to connect SCL and SDA of the BME280 module.
Pin D3 is used to provide power for the BME module and is only activated when needed.
![Breadboard](/images/breadboard.PNG)

## Code
Please rename the config.cpp.template to config.cpp and set your coresponding credentials and parameters

## Images
![Prototype](/images/prototype.jpg)

![18650+Charger](/images/18650+charger.jpg)

![wireing](/images/wireing.jpg)
