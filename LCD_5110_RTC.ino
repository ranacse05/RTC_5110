#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

RTC_DS1307 rtc;
Adafruit_PCD8544 display = Adafruit_PCD8544(3,4,5,6,7);


void setup () {
  Serial.begin(57600);

  display.begin();

  /* Change the contrast using the following API*/
  display.setContrast(57);

  /* Clear the buffer */
  display.clearDisplay();
  
  /* Now let us display some text */
  display.setTextColor(BLACK);
  display.setCursor(4,8);
  display.setTextSize(1);
  display.println("|Electronics|");
  display.display();
  //delay(1000);    

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop() {
   display.clearDisplay();

   DateTime now = rtc.now();

  //buffer can be defined using following combinations:
  //hh - the hour with a leading zero (00 to 23)
  //mm - the minute with a leading zero (00 to 59)
  //ss - the whole second with a leading zero where applicable (00 to 59)
  //YYYY - the year as four digit number
  //YY - the year as two digit number (00-99)
  //MM - the month as number with a leading zero (01-12)
  //MMM - the abbreviated English month name ('Jan' to 'Dec')
  //DD - the day as number with a leading zero (01 to 31)
  //DDD - the abbreviated English day name ('Mon' to 'Sun')

   char buf1[] = "hh:mm:ss";
   Serial.println(now.toString(buf1));

   char buf2[] = "YYMMDD-hh:mm:ss";
   Serial.println(now.toString(buf2));

   char buf3[] = "Today is DDD, MMM DD YYYY";
   Serial.println(now.toString(buf3));

   char buf4[] = "DD-MM-YYYY";
   Serial.println(now.toString(buf4));
   
     /* Now let us display some text */
  display.setTextColor(BLACK);
  display.setCursor(5,8);
  display.setTextSize(1);
  display.println(buf4);
  display.setTextColor(BLACK);
  display.setCursor(5,20);
  display.setTextSize(1);
  display.println(buf1);
  display.display();
   delay(1000);
}
