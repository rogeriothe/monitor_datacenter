#include "DHT.h"
#include "EmonLib.h"

#define VOLT_CAL 211.6


#define DHTPIN A0 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

EnergyMonitor emon1;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  emon1.current(1, 545);
  dht.begin();
}

void loop()
{
  float t = getTemp();
  float h = getHumid();
  float v = getVolt();

  if (isnan(t) || isnan(h) || isnan(v))
  {
    Serial.println("Failed to read sensor.");
  }
  else
  {
    Serial.print("Voltagem: ");
    Serial.print(v);
    Serial.println(" V ");
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.println(" % ");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
    delay(1000);
  }
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
