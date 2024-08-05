#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2     // what pin we're connected to

 LiquidCrystal_I2C lcd(0x27, 16, 2);

int redPin = 3;

void setup() {
  // put your setup code here, to run once:

  lcd.init();
    lcd.backlight();

    pinMode(redPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


digitalWrite(redPin, HIGH);
     lcd.setCursor(0, 0);
    lcd.print("Testing");
 

}
