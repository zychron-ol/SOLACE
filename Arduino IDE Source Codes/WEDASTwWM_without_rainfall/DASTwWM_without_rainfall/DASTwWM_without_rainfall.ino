#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servohori;
int servoh = 90;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti;
int servov = 90;
int servovLimitHigh = 160;
int servovLimitLow = 20;

void setup()
{
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("Temp = ");
  lcd.setCursor(0, 1);
  lcd.print("Humidity = ");

  servohori.attach(10);
  servohori.write(90);
  servoverti.attach(9);
  servoverti.write(90);
  delay(500);
}

void loop()
{
  // Read temperature and humidity from DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Display temperature and humidity on LCD
  lcd.setCursor(7, 0);
  lcd.print(temperature);
  lcd.setCursor(11, 1);
  lcd.print(humidity);

  // Servo control based on sensor readings
  int ldrtopl = A2; //top left LDR green
  int ldrtopr = A3; //top right LDR yellow
  int ldrbotl = A1; // bottom left LDR blue
  int ldrbotr = A0; // bottom right LDR orange

  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);

  int avgtop = (topl + topr) / 2;
  int avgbot = (botl + botr) / 2;
  int avgleft = (topl + botl) / 2;
  int avgright = (topr + botr) / 2;

  if (avgtop < avgbot)
  {
    servohori.write(servoh + 1);
    if (servoh > servohLimitHigh)
    {
      servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    servohori.write(servoh - 1);
    if (servoh < servohLimitLow)
    {
      servoh = servohLimitLow;
    }
    delay(10);
  }
  else
  {
    servohori.write(servoh);
  }

  if (avgleft > avgright)
  {
    servoverti.write(servov + 1);
    if (servov > servovLimitHigh)
    {
      servov = servovLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servoverti.write(servov - 1);
    if (servov < servovLimitLow)
    {
      servov = servovLimitLow;
    }
    delay(10);
  }
  else
  {
    servoverti.write(servov);
  }

  delay(1000);
}
