
#include <Time.h>
#include <Wire.h>
#include <SD.h>
#include <DS1307RTC.h>


const int chipSelect = 10;
tmElements_t tm;

void setup()
{ 

  bool config = false;
  tmElements_t tm_copy;

  Serial.begin(9600);
  
  Serial.print("Initializing SD Card... ");
  if (!SD.begin(chipSelect)){
    Serial.println("card initialization failed...");
    return;
  }
  
  Serial.println("card initialized.");


}

void loop()
{
  char *datestamp; 
  tmElements_t tm;
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile){
    if (RTC.read(tm)) {

      Serial.print(tmYearToCalendar(tm.Year));
      Serial.print("/");
      Serial.print(tm.Month);
      Serial.print("/");
      Serial.print(tm.Day);
      Serial.print(" - ");

      print2digits(tm.Hour);
      Serial.print(" : ");
      print2digits(tm.Minute);
      Serial.print(" : ");
      print2digits(tm.Second);
      Serial.println();
    }
  }
  dataFile.close();
  delay(1000);
}

void print2digits(int number) {
  if (number >= 0 && number<10) {
    Serial.write('0');
  }
  Serial.print(number);
}
