#!/bin/sh

# CONTROL register
#
# D1-D0
#  stand by : 0
#  forward  : 1
#  revarsal : 2
#  brake    : 3
#
# D7-D2
#  0x06 0.48V
#  0x07 0.56V
#  0x08 0.64V
#  ...
#  0x3f 5.06V

# stand by, 5.06V
#   0 + (0x3f << 2) = 252
sudo echo "set_motor 100 252" >> /dev/rfcomm0
cat /dev/rfcomm0
# sleep 1

# forward, 5.06V
#   1 + (0x3f << 2) = 253
# echo "set_motor 100 253" >> /dev/rfcomm0
# sleep 1

# stand by, 5.06V
#   0 + (0x3f << 2) = 252
# sudo echo "set_motor 100 252" >> /dev/rfcomm0
# sleep 1

# revarsal, 5.06V
#   2 + (0x3f << 2) = 254
# sudo echo "set_motor 100 254" >> /dev/rfcomm0
# sleep 1

# brake, 5.06V
#   3 + (0x3f << 2) = 255
# sudo echo "set_motor 100 255" >> /dev/rfcomm0
# sleep 1
