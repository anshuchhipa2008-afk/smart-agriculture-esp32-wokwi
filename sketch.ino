#define BLYNK_TEMPLATE_ID "TMPL3tGZEsm6x"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation"
#define BLYNK_AUTH_TOKEN "G5DshaONied8c51l3C316VEOp-IlxWGY"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define SOIL_PIN 34
#define PUMP_PIN 23
#define DHT_PIN 4
#define DHT_TYPE DHT22

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHT_TYPE);

bool manualMode = false;
bool manualPump = false;
BlynkTimer timer;

BLYNK_WRITE(V4) {
  manualPump = param.asInt();
  manualMode = true;
  if (manualPump) digitalWrite(PUMP_PIN, HIGH);
  else digitalWrite(PUMP_PIN, LOW);
}

void sendData() {
  int soilRaw = analogRead(SOIL_PIN);
  int soilPercent = map(soilRaw, 4095, 0, 0, 100);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp)) temp = 25;
  if (isnan(hum)) hum = 60;

  if (!manualMode) {
    if (soilPercent < 30) digitalWrite(PUMP_PIN, HIGH);
    else digitalWrite(PUMP_PIN, LOW);
  }

  bool pumpOn = digitalRead(PUMP_PIN);

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, soilPercent);
  if (pumpOn) Blynk.virtualWrite(V3, "ON");
  else Blynk.virtualWrite(V3, "OFF");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(soilPercent);
  lcd.print("% ");
  if (soilPercent < 30) lcd.print("DRY");
  else lcd.print("WET");
  lcd.setCursor(0, 1);
  if (pumpOn) lcd.print("Pump: ON ");
  else lcd.print("Pump: OFF");

  Serial.print("Soil: "); Serial.print(soilPercent);
  Serial.print(" Temp: "); Serial.print(temp);
  Serial.print(" Hum: "); Serial.print(hum);
  Serial.print(" Pump: "); Serial.println(pumpOn ? "ON" : "OFF");
}

void setup() {
  Serial.begin(115200);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("Connecting...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.clear();
  timer.setInterval(2000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
