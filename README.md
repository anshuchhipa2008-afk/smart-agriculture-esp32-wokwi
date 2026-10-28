
# 🌱 Smart Agriculture Monitoring System

IoT Based Real-Time Soil Moisture, Temperature & Humidity Monitoring using ESP32 & Wokwi Simulator.

### 🚀 Live Simulation
**Wokwi Link:** https://wokwi.com/projects/479114791569296385

**GitHub Link:** https://github.com/anshuchhipa2008-afk/smart-agriculture-esp32-wokwi

### 🛠️ Components Used
- ESP32 DevKit V1
- DHT22 Sensor (Temperature & Humidity)
- Potentiometer (Soil Moisture Simulation)
- LCD 1602 I2C Display
- Jumper Wires

### 🔌 Wiring Details
- LCD SDA -> ESP32 D21
- LCD SCL -> ESP32 D22
- DHT DATA -> ESP32 D4
- POT Signal -> ESP32 D34
- VCC -> 3.3V, GND -> GND

### 📊 Working
System reads temperature, humidity from DHT22 and soil moisture from potentiometer, then displays real-time data on 16x2 LCD.
