#include <UIPEthernet.h>
#include <PubSubClient.h>

#include "DHT.h"
#include "EmonLib.h"

#define VOLT_CAL 211.6


#define DHTPIN A0 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

#define CLIENT_ID       "ArduinoMQTT"
#define TOPIC1          "datacenter/temperature"
#define TOPIC2          "datacenter/humidity"
#define TOPIC3          "datacenter/voltage"
#define PUBLISH_DELAY   5000

uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
byte ip[] = { 10, 1, 1, 2 };
IPAddress mqttServer(10,1,1,5);

EthernetClient ethClient;
PubSubClient mqttClient;


EnergyMonitor emon1;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  emon1.current(1, 545);
  dht.begin();
    
  Ethernet.begin(mac, ip);
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.println();
  // setup mqtt client
  mqttClient.setClient(ethClient);
  mqttClient.setServer(mqttServer, 1883);
  Serial.println(F("Ready to send data"));
  
}

float getTemp() {
  float t = dht.readTemperature();
  return t;
}

float getHumid() {
  float h = dht.readHumidity();
  return h;
}

float getVolt(){
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  return Irms;
}

void loop() {  
  sendData();
  delay(PUBLISH_DELAY);
  mqttClient.loop();
}

void sendData(){
  char msgBuffer[20];
  
  float t = getTemp();
  float h = getHumid();
  float v = getVolt();

  if(mqttClient.connect(CLIENT_ID, "admin", "password"))
  {
      char msgBuffer[20];
      mqttClient.publish(TOPIC1, dtostrf(t, 6, 2, msgBuffer));
      Serial.println("Temp: " + String(t));
      
      
      mqttClient.publish(TOPIC2, dtostrf(h, 6, 2, msgBuffer));
      Serial.println("Umid: " + String(h));
            
      mqttClient.publish(TOPIC3, dtostrf(v, 6, 2, msgBuffer));
      Serial.println("Volt: " + String(v));
  }
    
}
