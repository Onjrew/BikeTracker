
#include <stdlib.h>
#include <Time.h>
#include <Wire.h>
#include <SD.h>
#include <DS1307RTC.h>

const int chipSelect = 10;
tmElements_t tm;
char filename[13];
File data_file;
int year_num;
int month_num;
int day_num;
int hour_num;
int minute_num;
int second_num;
char year_str[5];
char month_str[3];
char day_str[3];
char hour_str[3];
char minute_str[3];
char second_str[3];
char date_stamp[13];
char time_stamp[13];

void make_2digit_str(int num, char *str)
{
  char tmp1[3];
  char tmp2[3];
  if (num<10){
    dtostrf(num, 1, 0, tmp1);
    sprintf(tmp2, "0%s", tmp1);
    strcpy(str, tmp2);
  } else {
    dtostrf(num, 2, 0, str);
  }
}

void setup()
{ 
  

  Serial.begin(9600);
  
  Serial.print("Initializing SD Card... ");
  if (!SD.begin(chipSelect)){
    Serial.println("card initialization failed...");
    return;
  }
  
  Serial.println("card initialized.");

  RTC.read(tm);

  year_num  = tmYearToCalendar(tm.Year);
  month_num = tm.Month;
  day_num   = tm.Day;

  dtostrf(year_num, 4, 0, year_str);

  make_2digit_str(month_num, month_str);
  make_2digit_str(day_num, day_str);

  hour_num = tm.Hour;
  minute_num = tm.Minute;
  second_num = tm.Second;

  make_2digit_str(hour_num, hour_str);
  make_2digit_str(minute_num, minute_str);
  make_2digit_str(second_num, second_str);

  sprintf(date_stamp, "%s%s%s", year_str, month_str, day_str);
  sprintf(time_stamp, "%s%s%s", hour_str, minute_str, second_str);
  sprintf(filename, "%s%s%s%s.log", month_str, day_str, hour_str, minute_str);  

  data_file = SD.open(filename, FILE_WRITE);
  if (data_file){
    Serial.print("Successfully created file: ");
    Serial.println(filename);
    data_file.write(time_stamp);
    data_file.close();
  } else {
    Serial.print("Failed to create file: ");
    Serial.println(filename);
  }

}


void loop()
{
  data_file = SD.open(filename, FILE_WRITE);

  if (data_file){
    if (RTC.read(tm)) {

      hour_num = tm.Hour;
      minute_num = tm.Minute;
      second_num = tm.Second;

      make_2digit_str(hour_num, hour_str);
      make_2digit_str(minute_num, minute_str);
      make_2digit_str(second_num, second_str);

      sprintf(time_stamp, ",%s%s%s", hour_str, minute_str, second_str);
      
      data_file.write(time_stamp);
    }
  } else {
    Serial.print("Could not create data_file: ");
    Serial.println(filename);
  }
  data_file.close();
  delay(10000);
}

