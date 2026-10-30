# Smart Agriculture Monitoring - ESP32 Wokwi

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

### ⚙️ Working
System reads temperature, humidity from DHT22 and soil moisture from potentiometer, then displays on LCD and controls water pump based on soil moisture threshold.

### ✅ Level 3 - Wokwi Test Proof (Verified)

#### 1. DRY Condition (Soil 0%) - Pump ON
![DRY Pump ON](./level3-dry-pump-on.jpeg)

#### 2. WET Condition (Soil 80%) - Pump OFF
![WET Pump OFF](./level3-wet-pump-off.jpeg)

#### 3. DHT22 Sensor Working
![Temp Humidity](./level3-temp-humidity.jpeg)

**Result:** Soil Moisture Threshold Logic Verified - DRY=ON, WET=OFF
