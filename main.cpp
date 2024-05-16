#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPIN 2 
#define DHTTYPE DHT11

// Definicja niestandardowych znaków
const uint8_t termometr[8] = {
  B00100,
  B00111,
  B00100,
  B00100,
  B01110,
  B11111,
  B11111,
  B01110
};

const uint8_t kropla[8] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110
};

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();

  // Definicja niestandardowych znaków
  lcd.createChar(0, (uint8_t*)termometr);
  lcd.createChar(1, (uint8_t*)kropla);
}

void loop() {
  delay(500);

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)) {
    Serial.println(F("Błąd odczytu z czujnika DHT11"));
    return;
  }

  
  Serial.print(F("T: "));
  Serial.print(temp);
  Serial.print(F("C, H: "));
  Serial.print(humidity);
  Serial.println(F("%"));

  
  lcd.clear(); 

  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.print(F(": "));
  lcd.print(temp);
  lcd.print(F(" C"));

  lcd.setCursor(0, 1);
  lcd.write(byte(1)); 
  lcd.print(F(": "));
  lcd.print(humidity);
  lcd.print(F(" %"));

  delay(500); 
}
