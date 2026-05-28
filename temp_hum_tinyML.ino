#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- EMBEDDED ML COEFFECIENTS ---
// Trained via Multiple Linear Regression model
const float BETA_0 = -8.421;  // Intercept offset
const float BETA_1 = 0.284;   // Temperature weight coefficient
const float BETA_2 = 0.057;   // Humidity weight coefficient

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("TinyML Predictor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
}

void loop() {
  // DHT-11 takes roughly 250ms to sample data
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Guard clause against temporary sensor reading failure
  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  // --- TINYML ML INFERENCE ENGINE ---
  // Computing mathematical prediction vector equation in real-time
  float predictedComfort = BETA_0 + (BETA_1 * t) + (BETA_2 * h);

  // Constraints boundary checks to normalize indices
  if (predictedComfort < 0.0) predictedComfort = 0.0;
  if (predictedComfort > 5.0) predictedComfort = 5.0;

  // --- OUTPUT VISUALIZATION LAYER ---
  lcd.clear();
  
  // Row 1: Print live data telemetry
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print((int)t);
  lcd.print("C H:");
  lcd.print((int)h);
  lcd.print("% ML:");
  lcd.print(predictedComfort, 1);

  // Row 2: Map continuous values to discrete structural classifications
  lcd.setCursor(0, 1);
  if (predictedComfort <= 1.5) {
    lcd.print("Comfort: PERFECT");
  } else if (predictedComfort > 1.5 && predictedComfort <= 3.0) {
    lcd.print("Comfort: NORMAL ");
  } else if (predictedComfort > 3.0 && predictedComfort <= 4.2) {
    lcd.print("Comfort: STUFFY ");
  } else {
    lcd.print("Comfort: WARNING");
  }

  // Debug monitoring output to computer terminal
  Serial.print("Live Temp: "); Serial.print(t);
  Serial.print(" | Humidity: "); Serial.print(h);
  Serial.print(" | Predicted AI Score: "); Serial.println(predictedComfort);

  delay(3000); // Re-calculate trends every 3 seconds
}
