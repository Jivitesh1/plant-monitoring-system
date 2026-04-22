#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";


#define SOIL_PIN 34
#define RELAY_PIN 26
#define DHT_PIN 4
#define DHT_TYPE DHT11


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;


int moistureThreshold = 40; 
bool manualPump = false;

void readSensors() {
  // Soil moisture reading (0–4095)
  int rawValue = analogRead(SOIL_PIN);

  // Convert to percentage (invert because dry = high value)
  int moisturePercent = map(rawValue, 4095, 1500, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("% | Temp: ");
  Serial.print(temp);
  Serial.print("°C | Humidity: ");
  Serial.println(hum);

  Blynk.virtualWrite(V0, moisturePercent);
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);

  if (!manualPump) {
    if (moisturePercent < moistureThreshold) {
      digitalWrite(RELAY_PIN, LOW);  // Pump ON (active LOW relay)
    } else {
      digitalWrite(RELAY_PIN, HIGH); // Pump OFF
    }
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("Moisture: ");
  display.print(moisturePercent);
  display.println("%");

  display.setCursor(0, 15);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.setCursor(0, 30);
  display.print("Humidity: ");
  display.print(hum);
  display.println("%");

  display.setCursor(0, 45);
  display.print("Pump: ");
  if (digitalRead(RELAY_PIN) == LOW)
    display.println("ON");
  else
    display.println("OFF");

  display.display();
}

BLYNK_WRITE(V3) {
  int value = param.asInt();
  manualPump = value;

  if (manualPump) {
    digitalWrite(RELAY_PIN, LOW);  // Force ON
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Back to AUTO
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // OFF initially

  dht.begin();

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // WiFi + Blynk
  Blynk.begin(auth, ssid, pass);

  // Timer (every 2 sec)
  timer.setInterval(2000L, readSensors);
}

// ------------------- LOOP -------------------
void loop() {
  Blynk.run();
  timer.run();
}