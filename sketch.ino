#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>



//RTC inittialization
#include <RTClib.h> 
 RTC_DS1307 rtc;  





#define DHTPIN 2   // Pin connected to DHT sensor
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

bool humidityCheck;
bool temperatureCheck;
bool lightCheck;

// For night
bool lightNightCheck;
bool temperatureNightCheck;

float humidity;
float temperature;
float lux;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LDR_PIN A0  // Pin connected to LDR

const float GAMMA = 0.7;
const float RL10 = 50;

int redPin = 3;
int greenPin = 4;

const unsigned long PRINT_INTERVAL = 5000; // 5 seconds
unsigned long previousMillis = 0;

void setup() {
    Serial.begin(9600);
    dht.begin();
    
    pinMode(LDR_PIN, INPUT);
    
    lcd.init();
    lcd.backlight();
    
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);


     if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1); // Halt execution
    }
}

void loop() {

DateTime now = rtc.now();
    // Read sensor values
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    
    int analogValue = analogRead(LDR_PIN);
    float voltage = analogValue / 1024.0 * 5.0;
    float resistance = 2000 * voltage / (1 - voltage / 5.0);
    lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
    
      unsigned long currentMillis = millis();

    // Print sensor values at the defined interval
    if (currentMillis - previousMillis >= PRINT_INTERVAL) {
        previousMillis = currentMillis;
        
        // Print sensor values for debugging
        Serial.print("Time: ");
        Serial.print(now.hour());
        Serial.print(":");
        Serial.print(now.minute());
        Serial.print(":");
        Serial.print(now.second());




        Serial.print(" - Humidity: ");
        Serial.print(humidity);
        Serial.print(" %, Temp: ");
        Serial.print(temperature);
        Serial.print(" Celsius, Light lux: ");
        Serial.println(lux);
        
        // Update LCD display
        lcd.setCursor(0, 0);
        lcd.print("Humidity:");
        lcd.setCursor(10, 0);
        lcd.print(humidity);
        lcd.setCursor(0, 1);
        lcd.print("Temp:");
        lcd.setCursor(10, 1);
        lcd.print(temperature);
        lcd.setCursor(0, 1);
        lcd.print("Lux:");
        lcd.setCursor(10, 1);
        lcd.print(lux);
    }


    // Call day or night checks based on your logic
    bool isDaytime = true;  // Replace with actual day/night detection logic
    
    if (isDaytime) {
        dayTimeCheck();
    } else {
        nightTimeCheck();
    }

    // Update LCD display
    lcd.setCursor(0, 0);
    lcd.print("Humidity:");
    lcd.setCursor(10, 0);
    lcd.print(humidity);

    delay(2000);  // Delay between readings
}

void dayTimeCheck() {
    checkMoisture();
    handleDayTimeTemperature();
    handleDayTimeLight();
    
    if (temperatureCheck == true  && humidityCheck == true  && lightCheck == true) {
        greenColor();
    } else {
        redColor();
    }
}

boolean checkMoisture() { 
    if (humidity >= 40 && humidity <= 60)  {

      humidityCheck = true;
    }
 else {
humidityCheck = false;
 }
}

boolean handleDayTimeTemperature() {
      if (temperature >= 18 && temperature <= 24)
      {


temperatureCheck = true;
      }
      else {
temperatureCheck = false;
      }

}

boolean handleDayTimeLight() {
    if(lux >= 2000 && lux <= 5000) {

lightCheck = true;
    }
  else {

  lightCheck = false;
  }
  
}

void handleNightTimeTemperature() {
    if (temperature >= 15 && temperature <= 20) {

      temperatureNightCheck = true;
    }
    else {
temperatureNightCheck = false;
    }
}

void handleNightTimeLight() {
      if (lux >= 0 && lux <= 200) {
      
      lightNightCheck = true;
      }

    else {
lightNightCheck = false;
    }
}

void nightTimeCheck() {
    handleNightTimeLight();
    handleNightTimeTemperature();
    checkMoisture();
    
    if (temperatureNightCheck == true && lightNightCheck == true && humidityCheck == true) {
        greenColor();
    } else {
        redColor();
    }
}

// Color functions
void redColor() {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
}

void greenColor() {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
}

void yellowColor() {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
}
