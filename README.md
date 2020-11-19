# Quinary LED Art Clock

This clock untilizes base 5 to represent the time using 5 neopixels. I've written a lot more about the project on my blog:

http://spikesnell.com/index.php?entry=Quinary-LED-Art-Clock

Some key features of the clock are that it sets itself automatically via NTP when it is powered on, and it continues to sync with NTP every now and then to account for drift on the esp8266. It also adjusts for Daylight Savings Time automatically by checking against what the current date is and adjusting the offset appropriately.

The clock gets quite a bit less bright after 8pm so that it doesn't illuminate the room too much at night. It comes back to its normal brightness every morning at 8am.

The code makes use of the libraries NTPClient and FastLED which can be found here:

https://github.com/taranais/NTPClient

https://github.com/FastLED/FastLED

All of the settings are configurable via defines near the top of the sketch which may have to be adjusted depending on what timezone you are in.

The picture helps demonstrate how to read the clock:

![quinary clock](https://raw.githubusercontent.com/Crysknife007/quinary-led-clock/main/20201117_154320_HDR.jpg)

Each color represents a different digit in base 5. The picture above is how the time 15:43 is represented. 

