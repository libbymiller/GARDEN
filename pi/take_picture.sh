#!/bin/bash

DATE=$(date +"%Y-%m-%d_%H%M")

raspistill -o /home/pi/archive/$DATE.jpg &

wait %1

cp /home/pi/archive/$DATE.jpg /home/pi/camera/last_picture.jpg
