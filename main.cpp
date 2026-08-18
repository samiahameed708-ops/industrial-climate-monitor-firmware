#include <DHT.h>

#define DHTPIN 15          // DHT22 Sensor connected to GPIO 15
#define DHTTYPE DHT22      // Match the DHT22 sensor symbol
#define LED_WARNING 2     // Industrial Warning LED connected to GPIO 2

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("--- Industrial Smart Factory Monitor Initialized ---");
  pinMode(LED_WARNING, OUTPUT);
  dht.begin();
}

void loop() {
  delay(2000);
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("🚨 Error: Failed to read data from DHT22 factory sensor!");
    return;
  }

  Serial.print("Current Factory Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature > 35.0) {
    digitalWrite(LED_WARNING, HIGH); 
    Serial.println("⚠️ WARNING: Machinery Overheating Detected! Safety System Active.");
  } else {
    digitalWrite(LED_WARNING, LOW);  
    Serial.println("🟢 Status: Operational Temperature Normal.");
  }
}
