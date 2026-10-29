#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN 4
#define DHTTYPE DHT22
#define SOIL_PIN 34
#define RELAY_PIN 26
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  lcd.setCursor(0,0); lcd.print("Smart Agri MP");
  lcd.setCursor(0,1); lcd.print("MEXT 2028 Ready");
  delay(2000);
}
void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int soilRaw = analogRead(SOIL_PIN);
  int soilPercent = map(soilRaw, 4095, 0, 0, 100);
  if (soilPercent < 40) digitalWrite(RELAY_PIN, HIGH);
  else digitalWrite(RELAY_PIN, LOW);
  Serial.print("Soil: "); Serial.print(soilPercent);
  Serial.print("% Pump: "); Serial.println(digitalRead(RELAY_PIN) ? "ON" : "OFF");
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("S:"); lcd.print(soilPercent); lcd.print("% "); lcd.print(digitalRead(RELAY_PIN) ? "P:ON" : "P:OFF");
  lcd.setCursor(0,1); lcd.print("T:"); lcd.print(temp,1); lcd.print("C H:"); lcd.print(hum,0); lcd.print("%");
  delay(3000);
}