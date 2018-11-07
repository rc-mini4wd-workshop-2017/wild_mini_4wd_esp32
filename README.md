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

since v0.0.3

#### synopsis

```
set_loglevel <loglevel>
```

loglevel : TRACE, DEBUG, INFO, WARN, ERROR, or FATAL

#### example

```
$ set_loglevel TRACE
[INFO ] set_loglevel TRACE
[INFO ] set_loglevel: set TRACE
[INFO ] set_loglevel: returns 0

result: 0
```

### log

Show latest logs.
The log capacity is 64.

since v0.0.3

#### synopsis

```
log
```

#### example

```
$ log
[INFO ] Quattro Ace started...
[INFO ] log
[INFO ] log: returns 0

result: 0
```

### info

Show system info.

since v0.0.3

#### synopsis

```
info
```

#### example

```
$ info
[INFO ] info
version=0.0.6
[INFO ] info: returns 0

result: 0
```

### get_button_state

Get button state.
HIGH or LOW.

since v0.0.3

#### synopsis

```
get_button_state
```

#### example

```
$ get_button_state
[INFO ] get_button_state
button state: not pressed
[INFO ] get_button_state: returns 0

result: 0
```

### get_distance

Get distance(cm).

since v0.0.3

#### synopsis

```
get_distance
```

#### example

```
$ get_distance
[INFO ] get_distance
[INFO ] get_distance: returns 107

result: 107
```

### set_digital

Set digital pin.
HIGH or LOW.

since v0.0.3

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
[INFO ] set_digital 26 HIGH
[INFO ] set_digital: returns 0

result: 0
```

### fire_led_gun

Fire led gun.

1. set High
2. wait 100ms
3. set Low

since v0.0.6

#### synopsis

```
fire_led_gun <pin>
```

pin : 0, 1, 2, ...

[pinmap](https://raw.githubusercontent.com/gojimmypi/ESP32/master/images/myESP32%20DevKitC%20pinout.png)

#### example

```
$ fire_led_gun 15
[INFO ] fire_led_gun 15
[INFO ] fire_led_gun: returns 0

result: 0
```

### set_servo

Set servo angle.

since v0.0.3

#### synopsis

```
set_servo <degrees>
```

degrees : from 0 to 180

[pinmap](https://raw.githubusercontent.com/gojimmypi/ESP32/master/images/myESP32%20DevKitC%20pinout.png)

#### example

```
$ set_servo 90
[INFO ] set_servo 90
[INFO ] set_servo: returns 0

result: 0
```

### drive_steering

Drive steering.

since v0.0.3

#### synopsis

```
drive_steering <direction>
```

direction : FORWARD, RIGHT, LEFT (default: FORWARD)

#### example

```
$ drive_steering RIGHT
[INFO ] drive_steering RIGHT
[INFO ] drive_steering: returns 0

result: 0
```

### set_motor

Set motor pin(I2C).

since v0.0.3

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
[INFO ] set_motor 41
[INFO ] set_motor: returns 0

result: 0
```

revarsal (slow)

```
$ set_motor 42
[INFO ] set_motor 42
[INFO ] set_motor: returns 0

result: 0
```

### drive_motor

since v0.0.5

#### synopsis

```
drive_motor <vset> <until> <value>
```

vset : from 0 to 255 (default: 0)
       see DRV8330 datasheet
until : UNTIL_TIME, UNTIL_NEAR, UNTIL_BUMPER
value(option) : seconds if UNTIL_TIME. cm if UNTIL_NEAR.

#### example

```
$ drive_motor 61 UNTIL_TIME 2
[INFO ] drive_motor 61 UNTIL_TIME 2
[INFO ] drive_motor: returns 0

result: 0
$ drive_motor 61 UNTIL_NEAR 20
drive_motor 61 UNTIL_NEAR 20
[INFO ] drive_motor 61 UNTIL_NEAR 20
[ERROR] get_distance: max distance
[INFO ] drive_motor: detected UNTIL_NEAR
[INFO ] drive_motor: returns 0

result: 0
$ drive_motor 61 UNTIL_BUMPER
drive_motor 61 UNTIL_BUMPER
[INFO ] drive_motor 61 UNTIL_BUMPER
[INFO ] drive_motor: timeout
drive_motor: timeout
[INFO ] drive_motor: returns 0

result: 0
```

### reset

Reset motor and servo.

since v0.0.5

#### synopsis

```
reset
```

#### example

```
$ reset
[INFO ] reset
[INFO ] reset: returns 0

result: 0
```

## How to build esp-32 FW

### Install platformio

see [PlatformIO > Docs > PlatformIO Core > Installation](http://docs.platformio.org/en/latest/installation.html)

### How to build

```
$ git clone git@github.com:rc-mini4wd-workshop-2017/wild_mini_4wd_esp32.git
$ cd wild_mini_4wd_esp32
$ pio run
```

### How to upload

```
$ pio run --target upload -e esp32dev
```
