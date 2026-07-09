# Pinouts diagram to use Bruce on Lilygo TTGO T-Watch (ESP32)

The TTGO T-Watch uses the standard backplane expansion. The backplane provides SPI, UART, SD card, and various peripherals.

## Default SPI Bus (backplane)
| Device  | SCK   | MISO  | MOSI  | CS    | GDO0/CE   |
| ---     | :---: | :---: | :---: | :---: | :---:     |
| SD Card | 14    | 2     | 15    | 13    | ---       |
| CC1101  | 14    | 2     | 15    | 32    | 39        |
| NRF24   | 14    | 2     | 15    | 38    | 37        |

| Device  | RX    | TX    | GPIO  |
| ---     | :---: | :---: | :---: |
| GPS     | 34    | 33    | ---   |
| CH9329  | 34    | 33    | ---   |
| IR RX   |  ---  | ---   | 15    |
| IR TX   |  ---  | ---   | 13    |

## I2C Buses
### Main I2C (AXP202, BMA423, PCF8563)
- SDA: 21
- SCL: 22

### Touch I2C (FT6236)
- SDA: 23
- SCL: 32

## Onboard Features
- Button: GPIO 36 (active LOW)
- Battery ADC: GPIO 34
- TFT Backlight: GPIO 12
- Vibrator Motor: GPIO 4 (2020 V1) or DRV2605 I2C (2020 V2+)
- IR Send: GPIO 13 (2020 V1)

## GPIO 36 and 17 are free for additional modules like FS1000A or other single-pin modules.