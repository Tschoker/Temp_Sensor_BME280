#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <config.cpp>


//D0 = Output for RST pin
//D1 = I2C CLK
//D2 = I2C SDA
//D3 = pwr supply BME280

Adafruit_BME280 bme;

WiFiClient espClient;
PubSubClient client(espClient);

float temp = 0.0;
float hum = 0.0;
float pressure = 0.0;
float bat = 0.0;
bool status;

void setup_wifi() {
 delay(10);
 // We start by connecting to a WiFi network
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(wifi_ssid);
 WiFi.begin(wifi_ssid, wifi_password);
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
}

void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  if (client.connect("nodemcu", mqtt_user, mqtt_password)) {
  Serial.println("connected");
  } else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 2 seconds");
  delay(2000);
  }
 }
}

void setup()
{
  //initialize serial
  Serial.begin(74880);
  while (!Serial); // Leonardo: wait for serial monitor

  //Activate power supply for sensor
  pinMode(D3,OUTPUT);
  digitalWrite(D3,HIGH);
  delay(50);
  Serial.println("Sensor powered on");

  //initiate WiFi
  setup_wifi();

  //connect MQTT
  client.setServer(mqtt_server, 18830);
  if (!client.connected()) {
   Serial.println("MQTT not connected - trying reconnect!");
   reconnect();
  }
  client.loop();

  //Connect sensor
  Wire.begin(D1, D2);
  status = bme.begin(0x76);
  if (!status) {
     Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }

  //read and send values
  Serial.println(F("BME280 values"));
  temp=bme.readTemperature();
  pressure=(bme.readPressure()/100.0F);
  hum=bme.readHumidity();
  //bat=analogRead (A0) / 1024.0F * 5.03148F; //see README how to calculate your value for 5.03148F

  Serial.println( String(temp).c_str());
  client.publish(temperature_topic, String(temp).c_str(), true);
  Serial.println( String(pressure).c_str());
  client.publish(pressure_topic, String(pressure).c_str(), true);
  Serial.println(String(hum).c_str());
  client.publish(humidity_topic, String(hum).c_str(), true);
  //Serial.println(String(bat).c_str());
  //client.publish(battery_topic, String(bat).c_str(), true);

  delay(100);


  //deactivate sensor pwr supply
  digitalWrite(D3,LOW);


  //go to sleep
  ESP.deepSleep(900e6);

}


void loop()
{

}
