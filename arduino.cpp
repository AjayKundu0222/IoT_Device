#include <DHT.h>
#include <RTClib.h>
#include <LedControl.h>

#define DHTPIN 2         // Digital pin connected to the DHT22 sensor
#define DHTTYPE DHT22    // DHT sensor type

#define RTC_SDA A4       // SDA pin for RTC module
#define RTC_SCL A5       // SCL pin for RTC module

DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 rtc;

LedControl lc = LedControl(11, 13, 10, 4);  // DIN, CLK, CS, number of MAX7219 modules

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false);       // turn off power saving, enables display
  lc.setIntensity(0, 8);       // sets brightness (0 to 15)
  lc.clearDisplay(0);          // clear display

  dht.begin();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
}

void loop() {
  // Read temperature and humidity from DHT22 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print temperature and humidity to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Display temperature and humidity on the MAX7219 LED matrix display
  displayTemperatureAndHumidity(temperature, humidity);

  // Read date and time from RTC module
  DateTime now = rtc.now();

  // Print date and time to the serial monitor
  Serial.print("Date: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print("  Time: ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(5000);  // Delay for 5 seconds
}

void displayTemperatureAndHumidity(float temperature, float humidity) {
  // Display temperature
  int temp = int(temperature);
  lc.setDigit(0, 7, temp / 10, false);
  lc.setDigit(0, 6, temp % 10, true);

  // Display humidity
  int hum = int(humidity);
  lc.setDigit(0, 4, hum / 10, false);
  lc.setDigit(0, 3, hum % 10, true);

  delay(5000);  // Display for 5 seconds
  lc.clearDisplay(0);  // Clear the display
}
