#include <RTCTimedEvent.h>
#include <Wire.h> //needed for I2C

void setup() {
  Serial.begin(9600);
  
  //set time to 31/12/2010 23:58:50
  RTCTimedEvent.time.second = 50;
  RTCTimedEvent.time.minute = 58;
  RTCTimedEvent.time.hour = 23;
  RTCTimedEvent.time.dayOfWeek  = 6;
  RTCTimedEvent.time.day = 31;
  RTCTimedEvent.time.month = 12;
  RTCTimedEvent.time.year = 2010;
  RTCTimedEvent.writeRTC();
  
  //initial buffer for 3 timers
  RTCTimedEvent.initialCapacity = sizeof(RTCTimerInformation)*3;

  //event for every day
  RTCTimedEvent.addTimer(0,         //minute
                         0,         //hour
                         TIMER_ANY, //day fo week
                         TIMER_ANY, //day
                         TIMER_ANY, //month
                         dayCall);
  
  //event for every hour
  RTCTimedEvent.addTimer(0,         //minute
                         TIMER_ANY, //hour
                         TIMER_ANY, //day fo week
                         TIMER_ANY, //day
                         TIMER_ANY, //month
                         hourCall);
  
  //event for every minute
  RTCTimedEvent.addTimer(TIMER_ANY, //minute
                         TIMER_ANY, //hour
                         TIMER_ANY, //day fo week
                         TIMER_ANY, //day
                         TIMER_ANY, //month
                         minuteCall);
}

void loop() {
  RTCTimedEvent.loop();
}

void minuteCall(RTCTimerInformation* Sender) {
  Serial.print("New minute: ");
  
  Serial.print(RTCTimedEvent.time.hour, DEC);
  Serial.print(":");
  Serial.print(RTCTimedEvent.time.minute, DEC);
  Serial.print(":");
  Serial.print(RTCTimedEvent.time.second, DEC);
  Serial.print("  ");
  Serial.print(RTCTimedEvent.time.month, DEC);
  Serial.print("/");
  Serial.print(RTCTimedEvent.time.day, DEC);
  Serial.print("/");
  Serial.println(RTCTimedEvent.time.year, DEC);
}

void hourCall(RTCTimerInformation* Sender) {
  Serial.print("New hour! ");
}

void dayCall(RTCTimerInformation* Sender) {
  Serial.print("New day! ");
}