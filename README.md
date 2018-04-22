# Wild mini 4wd ESP32

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
$ sudo stty -F /dev/rfcomm0 115200
$ echo info >> /dev/rfcomm0
$ cat /dev/rfcomm0
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
$ set_digital 13 HIGH
```

### set_servo

Set servo pin.

#### synopsis

```
set_servo <pin> <degrees>
```

pin : 0, 1, 2, ...

degrees : from 0 to 180

[pinmap](https://raw.githubusercontent.com/gojimmypi/ESP32/master/images/myESP32%20DevKitC%20pinout.png)

#### example

```
$ set_servo 13 0
```
