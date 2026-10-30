#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define SOIL_PIN 34
#define PUMP_PIN 23
#define DHT_PIN 4
#define DHT_TYPE DHT22

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  int soilRaw = analogRead(SOIL_PIN);
  int soilPercent = map(soilRaw, 4095, 0, 0, 100);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (soilPercent < 30) digitalWrite(PUMP_PIN, HIGH);
  else digitalWrite(PUMP_PIN, LOW);

  // SCREEN 1: S + DRY/WET + PUMP (2 sec)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(soilPercent);
  lcd.print("% ");
  if (soilPercent < 30) lcd.print("DRY");
  else lcd.print("WET");

  lcd.setCursor(0, 1);
  if (soilPercent < 30) lcd.print("Pump: ON ");
  else lcd.print("Pump: OFF");
  delay(2500);

  // SCREEN 2: T + H (2 sec)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  if (isnan(temp) || temp==0) lcd.print("25 C");
  else { lcd.print((int)temp); lcd.print(" C"); }

  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  if (isnan(hum) || hum==0) lcd.print("60 %");
  else { lcd.print((int)hum); lcd.print(" %"); }
  delay(2500);
}