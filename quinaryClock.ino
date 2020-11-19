// Quinary RGBPY LED Clock
// Spike Snell 2020
//
// Add ESP8266 board from https://arduino.esp8266.com/stable/package_esp8266com_index.json 
// ( File > Preferences, Tools > Board > Board Manager )

#include <NTPClient.h>     // https://github.com/taranais/NTPClient
#include <FastLED.h>       // https://github.com/FastLED/FastLED
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Define the number of leds
#define NUM_LEDS 5

// Define the data pin
#define DATA_PIN 4

// Set up the character arrays for the Wifi ssid and password
const char *ssid     = "********";
const char *password = "********";

// Define the UTC Time offsets, these are for Central time in North America
const long winterOffset = -21600;
const long summerOffset = -18000;

// Define the DST Start and end Months and Days
const int dstMonthStart = 3;
const int dstDayStart   = 8;
const int dstMonthEnd   = 11;
const int dstDayEnd     = 1;

// Define the bright and dim light intensity 0 - 255
const int bright = 88;
const int dim    = 15;

// Define the hour that daylight roughly starts and ends
const int hourDayStarts = 8;
const int hourDayEnds   = 20;

// Define the led digit colors
uint32_t color[] = {
  0x151000,        // 0, Dim Yellow
  0xAA00AA,        // 1, Purple
  0x0000FF,        // 2, Blue
  0x005500,        // 3, Green
  0xFF0000         // 4, Red
};

// Define NTP Client to get the time
WiFiUDP ntpUDP;

// Set up the Network Time Protocol Client, update with fresh time every 10 minutes
NTPClient timeClient(ntpUDP, "85.21.78.23", winterOffset, 600000);

// Set up the leds array
CRGB leds[NUM_LEDS];

// Setup our sketch
void setup() {

    // Connect to the wifi point
    WiFi.begin(ssid, password);

    // Wait for the wifi to be connected
    while ( WiFi.status() != WL_CONNECTED ) {
        delay(500);
    }

    // Start the time client
    timeClient.begin();

    // Add the leds array to the Fast Led Definition
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    
}

// Loop through this part every second
void loop() {

    // Update the time client to get the current time
    timeClient.update();
 
    // Adjust for daylight savings time
    adjustDst();

    // Parse the current time and prepare all the led colors
    parseTime();
    
    // Show all the leds
    FastLED.show();

    // Wait for 1 second
    delay(1000);
    
}

// Adjust for daylight savings time considerations
void adjustDst() {

    // Extract date
    String formattedDate = timeClient.getFormattedDate();

    // Get the current month string
    String month = formattedDate.substring(5, 7);

    // Get the current day string
    String day   = formattedDate.substring(8,10);

    // If we are within the defined daylight savings time period
    if ( (month.toInt() >  dstMonthStart && month.toInt() < dstMonthEnd)      ||
         (month.toInt() == dstMonthStart && day.toInt()   > dstDayStart - 1)  || 
         (month.toInt() == dstMonthEnd   && day.toInt()   < dstDayEnd)        ){

        // Set summer time
        timeClient.setTimeOffset(summerOffset);
        
    }

    // Else we must not be in daylight savings time
    else {
      
        // Set winter time
        timeClient.setTimeOffset(winterOffset);
      
    }
  
}

// Parse the current time and prepare all the led colors
void parseTime() {

    // Create our character buffers
    char timeBuffer[5];
    char minuteBuffer[3];
    char tempHourBuffer[2];
    char tempMinuteBuffer[3];

    // Set the leds bright if during the daytime
    if ( timeClient.getHours() > hourDayStarts - 1 && timeClient.getHours() < hourDayEnds ) {

        // Set leds to bright mode 
        FastLED.setBrightness(bright); 
      
    }

    // Else set the led's to be dim because it is nighttime
    else {

        // Set leds to dim mode 
        FastLED.setBrightness(dim); 
      
    }

    // Convert the current hours to base 5
    itoa(timeClient.getHours(),tempHourBuffer,5);

    // Convert the current minutes to base 5
    itoa(timeClient.getMinutes(),tempMinuteBuffer,5);

    // Pad 0's to the hour buffer and place it on the timeBuffer
    sprintf( timeBuffer, "%02s", tempHourBuffer );

    // Pad 0's onto the tempMinuteBuffer and place it on minuteBuffer
    sprintf( minuteBuffer, "%03s", tempMinuteBuffer );

    // Concatenate the timeBuffer and minuteBuffer
    strcat(timeBuffer, minuteBuffer);

    // Iterate over the timeBuffer and set all the leds
    for (int i = 0; i < strlen(timeBuffer); i++) {
      
        // Switch on the current timeBuffer digit and set each led's color
        switch(timeBuffer[i]) {
            case '0' :
                leds[i] = color[0];
                break;     
            case '1' :
                leds[i] = color[1];
                break;   
            case '2' :
                leds[i] = color[2];
                break;   
            case '3' :
                leds[i] = color[3];
                break;   
            default :
                leds[i] = color[4];     
        }

    }
  
}
