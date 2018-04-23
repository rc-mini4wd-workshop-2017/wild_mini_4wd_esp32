#!/bin/sh

sudo echo "set_servo 13 65" >> /dev/rfcomm0
sleep 0.5
sudo echo "set_servo 13 80" >> /dev/rfcomm0
sleep 0.5
sudo echo "set_servo 13 95" >> /dev/rfcomm0
sleep 0.5
sudo echo "set_servo 13 80" >> /dev/rfcomm0
sleep 0.5

