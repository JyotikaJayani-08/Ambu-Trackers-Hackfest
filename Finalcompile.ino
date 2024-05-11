#define BLYNK_TEMPLATE_ID "TMPL349H91dSS"
#define BLYNK_TEMPLATE_NAME "Shiven Sisodia"
#define BLYNK_AUTH_TOKEN "Tic_nyd0OmtLl2oqXewLNa_xhpny19GV"

#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "heartRate.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <BlynkSimpleEsp32.h>

#define WIFISSID "Shiven14" // Enter WifiSSID here
#define PASSWORD "14080311" // Enter password here
#define TOKEN "BBUS-TwiCNQl9hpRmoX5a4KA9WXhQ0tKqd2" // Ubidots' TOKEN
#define MQTT_CLIENT_NAME "shivenpreet" // MQTT client Name
#define VARIABLE_LABEL "ecg" // ubidots variable label
#define DEVICE_LABEL "ecg-monitoring" // ubidots device label
#define SENSORPIN A0 // Set the A0 as SENSORPIN


char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[10000];
char topic[150];
char str_sensor[10];
char str_millis[20];
double epochseconds = 0;
double epochmilliseconds = 0;
double current_millis = 0;
double current_millis_at_sensordata = 0;
double timestampp = 0;
int j = 0;

MAX30105 particleSensor;
BlynkTimer timer;

char auth[] = "Tic_nyd0OmtLl2oqXewLNa_xhpny19GV"; // Blynk authentication token
char ssid[] = "Shiven14"; // Your WiFi SSID
char pass[] = "14080311"; // Your WiFi password

#define MAX_BRIGHTNESS 255

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
uint16_t irBuffer[100]; // infrared LED sensor data
uint16_t redBuffer[100]; // red LED sensor data
#else
uint32_t irBuffer[100]; // infrared LED sensor data
uint32_t redBuffer[100]; // red LED sensor data
#endif

int32_t bufferLength;
int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;

byte pulseLED = 13;
byte readLED = 2;

WiFiClient ubidots;
PubSubClient client(ubidots);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.write(payload, length);
  Serial.println(topic);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  pinMode(SENSORPIN, INPUT);

  Serial.println();
  Serial.print("Waiting for WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);
  timeClient.update();
  epochseconds = timeClient.getEpochTime();
  epochmilliseconds = epochseconds * 1000;
  Serial.print("epochmilliseconds=");
  Serial.println(epochmilliseconds);
  current_millis = millis();
  Serial.print("current_millis=");
  Serial.println(current_millis);

  pinMode(pulseLED, OUTPUT);
  pinMode(readLED, OUTPUT);

  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30105 was not found. Please check wiring/power.");
    while (1);
  }
  Serial.println("Attach sensor to finger with rubber band.");

  byte ledBrightness = 60;
  byte sampleAverage = 4;
  byte ledMode = 2;
  byte sampleRate = 100;
  int pulseWidth = 411;
  int adcRange = 4096;

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, sendSensorData);
}

void sendSensorData() {
  bufferLength = 100;
  for (byte i = 0; i < bufferLength; i++) {
    while (particleSensor.available() == false)
      particleSensor.check();

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample();

    Serial.print("red=");
    Serial.print(redBuffer[i], DEC);
    Serial.print(", ir=");
    Serial.println(irBuffer[i], DEC);
  }

  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

  while (1) {
    for (byte i = 25; i < 100; i++) {
      redBuffer[i - 25] = redBuffer[i];
      irBuffer[i - 25] = irBuffer[i];
    }

    for (byte i = 75; i < 100; i++) {
      while (particleSensor.available() == false)
        particleSensor.check();

      digitalWrite(readLED, !digitalRead(readLED));

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample();

      Serial.print("red=");
      Serial.print(redBuffer[i], DEC);
      Serial.print(", ir=");
      Serial.print(irBuffer[i], DEC);

      Serial.print(", HR=");
      Serial.print(heartRate, DEC);
      Blynk.virtualWrite(V0, heartRate);

      Serial.print(", SPO2=");
      Serial.println(spo2, DEC);
      Blynk.virtualWrite(V2, spo2);
    }
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
  }
}

void loop() {
  Blynk.run();
  timer.run();

  if (!client.connected()) {
    reconnect();
    j = 0;
  }
  j = j + 1;
  Serial.print("j=");
  Serial.println(j);
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\": [", VARIABLE_LABEL);
  for (int i = 1; i <= 3; i++) {
    float sensor = analogRead(SENSORPIN);
    dtostrf(sensor, 4, 2, str_sensor);
    sprintf(payload, "%s{\"value\":", payload);
    sprintf(payload, "%s %s,", payload, str_sensor);
    current_millis_at_sensordata = millis();
    timestampp = epochmilliseconds + (current_millis_at_sensordata - current_millis);
    dtostrf(timestampp, 10, 0, str_millis);
    sprintf(payload, "%s \"timestamp\": %s},", payload, str_millis);
    delay(150);
  }

  float sensor = analogRead(SENSORPIN);
  dtostrf(sensor, 4, 2, str_sensor);
  current_millis_at_sensordata = millis();
  timestampp = epochmilliseconds + (current_millis_at_sensordata - current_millis);
  dtostrf(timestampp, 10, 0, str_millis);
  sprintf(payload, "%s{\"value\":%s, \"timestamp\": %s}]}", payload, str_sensor, str_millis);
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);
  Serial.println(payload);
}