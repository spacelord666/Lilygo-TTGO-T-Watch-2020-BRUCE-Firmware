# Bruce Firmware for LilyGO TTGO T-Watch (ESP32, non-S3)

## What is this?

This is a custom board port of **[Bruce](https://github.com/BruceDevices/firmware)** — a versatile ESP32 firmware focused on Red Team operations, offensive security, and wireless experimentation. It supports Wi-Fi attacks (Evil Portal, Wardriving, EAPOL handshake capture), Bluetooth/BLE scanning, RF signal analysis (CC1101, NRF24), IR, NFC/RFID (PN532), BadUSB, GPS, FM radio, and more.

## Target Device

**LilyGO TTGO T-Watch (original ESP32, non-S3)** — any variant of the T-Watch 2019, 2020 (V1/V2/V3), or 2021 that uses the ESP32 DOWDQ6 chipset with:

- ST7789 240x240 round display
- FT6236/FT6336 capacitive touch
- AXP202 power management unit
- BMA423 accelerometer
- PCF8563 RTC
- I2C sensor bus (GPIO 21/22)
- Touch I2C bus (GPIO 23/32)
- SPI backplane expansion (CC1101, NRF24, SD card)

**Not for the T-Watch S3** — this is a separate port for the original ESP32-based watches.

## Source Code

The board definition was created by adapting the existing [lilygo-t-display-s3](https://github.com/BruceDevices/firmware/tree/dev/boards/lilygo-t-display-s3) and [lilygo-t-display-ttgo](https://github.com/BruceDevices/firmware/tree/dev/boards/lilygo-t-display-ttgo) board configurations from the upstream Bruce firmware repository.

### Files created

| File | Purpose |
|------|---------|
| `boards/lilygo-t-watch/pins_arduino.h` | Pin mappings for TFT, touch, AXP202, CC1101, NRF24, I2C, SPI, UART, IR, SD, buttons |
| `boards/lilygo-t-watch/interface.cpp` | AXP202 PMU init, FT6236 touch handler, button input, battery monitoring, power-off |
| `boards/lilygo-t-watch/lilygo-t-watch.ini` | PlatformIO build environment with all device-specific build flags |
| `boards/lilygo-t-watch/connections.md` | Pinout reference diagram |
| `boards/_boards_json/lilygo-t-watch.json` | PlatformIO board JSON (ESP32, 16MB flash, QIO, PSRAM) |
| `boards/pinouts/pins_arduino.h` | Updated dispatch header with `T_WATCH` entry |

## Key Features in This Port

- ✅ Full 240x240 ST7789 TFT display with SMOOTH_FONT
- ✅ FT6236 capacitive touch (separate I2C bus)
- ✅ AXP202 PMU (battery percentage, charging status, power management)
- ✅ CC1101 sub-GHz radio (via backplane SPI)
- ✅ NRF24 (via backplane SPI)
- ✅ IR TX/RX
- ✅ BadUSB via UART
- ✅ GPS (backplane UART on GPIO 33/34)
- ✅ SD card (backplane SPI)
- ✅ BMA423 / PCF8563 / AXP202 on main I2C bus
- ✅ Deep sleep with button wake

## Compilation

Built with PlatformIO using the upstream Bruce firmware repository (branch `dev`):

```
git clone --branch dev https://github.com/BruceDevices/firmware.git
cd firmware
# Copy board files into place
pio run -e lilygo-t-watch
```

## Binary

`firmware.bin` — 3.5 MB, fits in 16MB flash (21.6% usage).
