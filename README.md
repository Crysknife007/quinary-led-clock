# Quinary LED Art Clock

This clock untilizes base 5 to represent the time using 5 neopixels. 

Some key features of the clock are that it sets itself automatically via NTP when it is powered on, and it continues to sync with NTP every now and then to account for drift on the esp8266. It also adjusts for Daylight Savings Time automatically by checking against what the current date is and adjusting the offset appropriately.

The clock gets quite a bit less bright after 8pm so that it doesn't illuminate the room too much at night. It comes back to its normal brightness every morning at 8am.

The code makes use of the libraries NTPClient and FastLED which can be found here:

https://github.com/taranais/NTPClient
https://github.com/FastLED/FastLED

All the settings are configurable via defines near the top of the sketch which may have to be adjusted depending on what timezone you are in.

The picture helps demonstrate how to read the clock:

