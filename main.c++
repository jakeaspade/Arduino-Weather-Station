// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 6     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11


// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int tempFer = true;


void setup() {
  lcd.begin(16,2);
  pinMode(13, INPUT);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}
  
void loop() {
  int button = digitalRead(13);
  // Determines if the temperature should be F or C
  if (button == HIGH){
    if (tempFer == true){
      tempFer == false;
      }
    else{
      tempFer = true;
      }
      
    }
    
  delay(1000);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  lcd.setCursor(0, 0);
  lcd.print(F("Humidity: "));
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print(F("Temp: "));
  if (tempFer == false){
    lcd.print((t * 1.8) + 32);
    lcd.print("C");
    }
  else{
    lcd.print(t);
    lcd.print("F");
    }

}