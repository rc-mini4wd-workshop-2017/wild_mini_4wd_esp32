# Wild mini 4wd ESP32

## Pin assign

| #    | Function |
| IO21 | SDA      |
| IO22 | SCL      |

## How to connect to ESP32

### from Linux

terminal 1

```
$ hcitool scan
Scanning ...
        xx:xx:xx:xx:xx:xx       Quattro Ace
$ sudo rfcomm connect hci0 xx:xx:xx:xx:xx:xx 2
Connected /dev/rfcomm0 to xx:xx:xx:xx:xx:xx on channel 2
Press CTRL-C for hangup
```

terminal 2

```
$ miniterm.py /dev/rfcomm0
info
version=0.0.1
```

## FAQ

### Invalid command [ATATAT...]

```
$ sudo systemctl stop ModemManager
$ sudo systemctl disable ModemManager
```

http://mattintosh.hatenablog.com/entry/20170702/1498985041

## CommandLineAPI

CommandLineAPI are enabled in Bluetooth (SPP).

### set_loglevel

Set log level.

#### synopsis

```
set_loglevel <loglevel>
```

loglevel : TRACE, DEBUG, INFO, WARN, ERROR, or FATAL

#### example

```
$ set_loglevel TRACE
[INFO ] loglevel: set TRACE
```

### log

Show latest logs.
The log capacity is 64.

#### synopsis

```
log
```

#### example

```
$ log
[INFO ] Quattro Ace started...
```

### info

Show system info.

#### synopsis

```
info
```

#### example

```
$ info
version=0.0.1
```

### set_digital

Set digital pin.
HIGH or LOW.

#### synopsis

```
set_digital <pin> <state>
```

pin : 0, 1, 2, ...

state : HIGH, or LOW

[pinmap](https://raw.githubusercontent.com/gojimmypi/ESP32/master/images/myESP32%20DevKitC%20pinout.png)

#### example

```
$ set_digital 26 HIGH
```

### set_servo

Set servo angle.

#### synopsis

```
set_servo <degrees>
```

degrees : from 0 to 180

[pinmap](https://raw.githubusercontent.com/gojimmypi/ESP32/master/images/myESP32%20DevKitC%20pinout.png)

#### example

```
$ set_servo 77
```

### drive_steering

Drive steering.

#### synopsis

```
drive_steering <direction>
```

direction : FORWARD, RIGHT, LEFT (default: FORWARD)

#### example

```
$ drive_steering RIGHT
```

### set_motor

Set motor pin(I2C).

#### synopsis

```
set_motor <vset>
```

vset : from 0 to 255 (default: 0)

see DRV8330 datasheet

#### example

stand by

```
$ set_motor 0
```

forward (slow)

```
$ set_motor 41
```

revarsal (slow)

```
$ set_motor 42
```

### drive_motor

Drive motor 2 seconds.

#### synopsis

```
drive_motor <vset> <until>
```

vset : from 0 to 255 (default: 0)
       see DRV8330 datasheet
until(option) : UNTIL_NEAR, UNTIL_BUMPER

#### example

```
$ drive_motor FORWARD
```

## How to build esp-32 FW

### Install platformio

see [PlatformIO > Docs > PlatformIO Core > Installation](http://docs.platformio.org/en/latest/installation.html)

### How to modify flash size

edit default.csv

```diff
--- ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/default.csv.default	2018-03-08 03:54:26.070449130 +0900
+++ ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/default.csv	2018-03-08 03:55:06.422823814 +0900
@@ -1,7 +1,7 @@
 # Name,   Type, SubType, Offset,  Size, Flags
 nvs,      data, nvs,     0x9000,  0x5000,
 otadata,  data, ota,     0xe000,  0x2000,
-app0,     app,  ota_0,   0x10000, 0x140000,
-app1,     app,  ota_1,   0x150000,0x140000,
+app0,     app,  ota_0,   0x10000, 0x200000,
+app1,     app,  ota_1,   0x210000,0x80000,
 eeprom,   data, 0x99,    0x290000,0x1000,
 spiffs,   data, spiffs,  0x291000,0x16F000,
```

### How to build

```
$ git clone git@github.com:rc-mini4wd-workshop-2017/wild_mini_4wd_esp32.git
$ cd wild_mini_4wd_esp32
$ pio run
```

### How to upload

```
$ pio run --target upload
```
