# Comfort-Study-Circumstance-Predictor
I have been distrubed weather and noise related issue! therefore, i wanted to know and maintain the level to make me focused.. although , it is a enumeration process of using sensors.. note: the comfort parameters are based on my inference..

# Comfort Study Circumstance Predictor (TinyML) 

An AI-driven climate assistant built with an Arduino that predicts human-perceived atmospheric comfort. Instead of using basic hardcoded rules, this project runs an embedded **Multiple Linear Regression model** on the edge to process live temperature and moisture data.

# How It Works
The human body experiences stuffiness as a combined effect of both heat and humidity. This project uses an embedded machine learning formula to process live telemetry:

predictedComfort = BETA_0 + (BETA_1 * t) + (BETA_2 * h)

The output is a real-time, continuous score from **0.0 (Perfect)** to **5.0 (Oppressive)** displayed directly on the screen.

---

# Components Used
* **Microcontroller**: Arduino Uno / Nano (ATmega328P)
* **Sensor**: DHT-11 Temperature & Humidity Sensor
* **Display**: 16x2 Character LCD with an I2C Backpack Module
* **Prototyping**: Breadboard and jumper wires

---

# 🔌 Pin Connections

Both the Arduino Uno and Nano use the standard hardware I2C pins ($A4$ and $A5$) to drive the display.


for wiring see the wiring_guide.txt
*Note: The I2C Display communication address is verified and locked at `0x27`.*

---

# Required Arduino Libraries

Install these libraries using the Arduino IDE Library Manager before uploading the code:
1. **DHT sensor library** *(by Adafruit)*
2. **LiquidCrystal_I2C** *(by Frank de Brabander)*

---

## ⚙️ Visual Output System

The screen updates every 3 seconds to show live readings and the AI comfort prediction tier:
* **Comfort: PERFECT** (Score $\le 1.5$) — Ideal indoor comfort conditions.
* **Comfort: NORMAL** (Score $1.6$ to $3.0$) — Standard indoor baseline climate.
* **Comfort: STUFFY** (Score $3.1$ to $4.2$) — Rising temperature or humidity saturation.
* **Comfort: WARNING** (Score $> 4.2$) — High climate discomfort; ventilation advised.

---

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## with the help of AIMode. It saves more time and its precise..
