# GARDEN

Pi and ESP code for a tiny garden

We have 4 window boxes, named after characters from Spaced. Each has an 
ESP8266 (Wimos D1 Mini) attached to a humidity sensor (e.g 
https://www.ebay.co.uk/itm/Soil-Hygrometer-Humidity-Detection-Module-Moisture-Testing-Sensor-Arduino-PI-DIY/322845304510?epid=24007814274&hash=item4b2b1466be:g:SrwAAOSwWZpZ7zLm)

The Pi runs a small python server (I put the startup code in /etc/rc.local as 
I'm lazy) and the ESPs connect to it and leave a reading periodically. In 
daylight hours the Pi sends a tweet with the readings and a photo once an 
hour, by parsing the last few entries in the server logs.

The logs aren't tidied up and the photos build up so you will run out of space.

I used a Pi Zero W plus camera in this case: https://shop.pimoroni.com/products/official-raspberry-pi-zero-case

Lots more tips here: http://www.gardenbot.org/howTo/soilMoisture/
