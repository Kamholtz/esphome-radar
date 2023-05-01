Determined using
https://crccalc.com/
crc-16 modbus
the hi and lo bit are swapped


55 start
0B length l = 11 (all bytes except start)
00 length h
04 command = actively report command
03 address 1 = report radar information
06 address 2 = movement sign parameter
00 data = n/a
00 
00 
00 
DD crc16 l
95 crc16 h




- The radar sensor was outputting the following constantly, so I used it to determine the CRC algorithm used

55 0B 00 04 03 06 00 00 00 00  (used this as input to the calculator)
DD 95 (checked that this is the CRC otuput)


55 0B 00 04 03 06 00 00 70 41 38 65

# First Test

## TX

0x55 0x07 0x00 0x01 0x03 0x05 0x28 0xED

0x55 start
0x07 length l
0x00 length h
0x01 read command
0x03 address code 1 = radar information
0x05 address code 2 = environmental status
0x28 crc l
0xED crc h

## RX

55 0A 00 03 03 05 01 00 FF 1C A3 

55
0A
00
03 passive report command
03 report radar information
05 environment status
01 someone is still
00
FF
1C
A3


# Read command (0x01)

## Radar information query (0x03)

### Environment status (0x05)

## System parameter (0x04)

### Threshold gear (0x0C)

- TX
  - 0x55 0x07 0x00 0x01 0x04 0x0C 0xEA 0xDB
- RX
  - 55 08 00 03 04 0C [07] 1A 0A
- Current gear value
  - 07

### Scene setting (0x10)

- TX
  - 0x55 0x07 0x00 0x01 0x04 0x10 0xEB 0x12
- RX
  - 55 08 00 03 04 10 [00] 53 08
- current scene setting
  - 00

### Force into unmannged stall (0x12)


## Change gear

0x55 0x08 0x00 0x02 0x04 0x0C 0x02 0xDB 0xF5









55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 08 00 02 04 12 02 D2 
55 
55 08 00 03 04 12 02 D3 A9 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0A 00 04 05 01 00 FF FF 84 14 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0B 00 04 03 06 00 00 00 00 DD 95 
55 0A 00 04 03 05 01 01 01 9D 04 
55 0A 00 04 03 05 01 01 01 9D 04 
55 0A 00 04 03 07 01 01 02 DC BD 
55 0A 00 04 03 07 01 01 03 1D 7D 
55 0B 00 04 03 06 00 00 50 41 21 A5 
55 0B 00 04 03 06 00 00 00 40 DC 65 
55 0A 00 04 05 01 01 01 01 14 34 



## Architectures

1. Make a custom component that is a UART device with MANY sensors. Each sensor represents one of the function_code/address_code_1/address_code_2 properties combinations
  - when a pull packet is received, you could publish to the sensor that represents that function/action addresses
  - much like: https://esphome.io/components/sensor/custom.html#bonus-sensors-with-multiple-output-values

2. Custom device could just read bytes until a packet is forced and then call an "on packet" callback which can be used to change components within the yaml file? 
  - pros: less custom code
  - cons: having to "wire up" functionality to display the state of things which you will always want if you have multiple radar sensors

2. Custom device could just read bytes until a packet is forced and then call an "on prescence change"/"on movement change" callback? 

- [ ] should each sensor be of specific type, or just use `Sensor()`

https://esphome.io/components/sensor/index.html


Sensors:

## DP1: Someone/Nobody No one to someone, report within 0.5s
From someone to no one, the output will
be stateless in about 1-2 minutes
- Binary
- get from pin
  - SensorDeviceClass.ENUM

  this and DP2 could be combined into a single tri state enum?

## DP2: Someone is stationary / Someone is
active
Static and dynamic switching, reporting
within 0.5 seconds
- Binary
- get from pin
  - SensorDeviceClass.ENUM

## DP3: Someone approaching the device/
Someone moves away from the device /
Someone moves without direction
Output status once every 2 seconds
- tri state - no, close, far away
  - SensorDeviceClass.ENUM

## DP4: Body Motion Amplitude Parameter 0 
– 100
Output data every 5 seconds
Reference ( Explanation of body motion
amplitude parameter output )
- Number - but somehow disable use changing it
- percentage
- could also have text/select/enum
  - SensorDeviceClass.ENUM

## DP5: Sensitivity settings 1 – 10 stops In the default scene mode, it can support
10 gear adjustments

- NOT a sensor
- number component - int

## DP7: Scene mode (bed, bathroom, hotel,
bedroom, office, default mode)
Adapt to different scenarios according to
the size of the area

- NOT a sensor
- select

## DP8: No false positive confirmation prompt
- no idea what this is

e.g.
// the responses to read/write commands
read command (0x01)/report radar information (0x03)/physical parameters (0x06)
passive_report command (0x03)/report radar information (0x03)/physical parameters (0x06) => 4 byte float data (movement sign)

- see 
  - 6.1 DP4 - Body Motion Amplitude Parameter 0-100
  - 6.2 meaning of percentages
