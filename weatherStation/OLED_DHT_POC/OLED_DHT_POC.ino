/*
 OLED Wiring
 GND to panel pin 1
 +5V to panel pin 2
 
 Panel data wiring (panel to Arduino)
 * LCD RS pin (pin 4) to digital pin 6
 * LCD R/W pin (pin 5) to digital pin 7
 * LCD Enable (pin 6) to digital pin 8
 * LCD D4 (pin 11) to digital pin 9
 * LCD D5 (pin 12) to digital pin 10
 * LCD D6 (pin 13) to digital pin 11
 * LCD D7 (pin 14) to digital pin 12
*/

// include the library code:
#include <Adafruit_CharacterOLED.h>
#include <DHT.h>

#define DHTPIN 2    // Arduino digital pin 2
//#define DHTTYPE DHT22
#define DHTTYPE DHT11

// initialize the library with the numbers of the interface pins
Adafruit_CharacterOLED lcd(6, 7, 8, 9, 10, 11, 12);
DHT dht(DHTPIN, DHTTYPE);

int minutes = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("DHT22 Starting");
  lcd.begin(16, 2);
  lcd.print("Humid%   Temp*F");
  dht.begin();
}

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  lcd.setCursor(0, 1);
  if (isnan(t) || isnan(h)) {
    Serial.println("DHT read failure");
    lcd.print("DHT fail");
  } else {
    float f = dht.convertCtoF(t);
    lcd.print(h);
    lcd.print("     ");
    lcd.print(f);
    Serial.print(minutes);
    Serial.print(": ");
    Serial.print(h);
    Serial.print("      ");
    Serial.println(f);
    delay(60000);
    minutes++;
  }
 }

