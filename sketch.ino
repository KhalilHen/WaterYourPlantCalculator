#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2   // what pin we're connected to
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);


float humidity;
float temperature; 
int chk;

 LiquidCrystal_I2C lcd(0x27, 16, 2);


int redPin = 3;
int greenPin = 4;
void setup() {
Serial.begin(9600);
  dht.begin();

  // put your setup code here, to run once:

  lcd.init();
    lcd.backlight();

    pinMode(redPin, OUTPUT);
        pinMode(greenPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
humidity = dht.readHumidity();
temperature = dht.readTemperature();


  Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temp: ");
    Serial.print(temperature);
    Serial.println(" Celsius");




if (humidity > 30 && humidity < 60)
{
 greenColor();

}
else {
redColor();
}



// delay(5000);

//  greenColor();

// delay(2000);





     lcd.setCursor(0, 0);
     lcd.print("Humidity:");
    lcd.print( humidity);
 delay(2000);

}





//Color functions
//RED = Give water

 void redColor() {

  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
}
//Green is plant has enough water

 void greenColor() {

    digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
}
//Yellow special situation  still thinking of a use case

 void yellowColor() {

  
    digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
}
