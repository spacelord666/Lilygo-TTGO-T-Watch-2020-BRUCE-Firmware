#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

#ifndef DEVICE_NAME
#define DEVICE_NAME "Lilygo TTGO T-Watch"
#endif

#define ADC_EN 14
#define ANALOG_BAT_PIN 34

#define SPI_SS_PIN 33
#define SPI_MOSI_PIN 15
#define SPI_MISO_PIN 2
#define SPI_SCK_PIN 14

#define SDCARD_CS 13
#define SDCARD_SCK SPI_SCK_PIN
#define SDCARD_MISO SPI_MISO_PIN
#define SDCARD_MOSI SPI_MOSI_PIN

#define USE_CC1101_VIA_SPI
#define CC1101_GDO0_PIN 39
#define CC1101_SS_PIN 32
#define CC1101_MOSI_PIN SPI_MOSI_PIN
#define CC1101_SCK_PIN SPI_SCK_PIN
#define CC1101_MISO_PIN SPI_MISO_PIN

#define USE_NRF24_VIA_SPI
#define NRF24_CE_PIN 37
#define NRF24_SS_PIN 38
#define NRF24_MOSI_PIN SPI_MOSI_PIN
#define NRF24_SCK_PIN SPI_SCK_PIN
#define NRF24_MISO_PIN SPI_MISO_PIN

#define USE_W5500_VIA_SPI
#define W5500_SS_PIN 38
#define W5500_MOSI_PIN SPI_MOSI_PIN
#define W5500_SCK_PIN SPI_SCK_PIN
#define W5500_MISO_PIN SPI_MISO_PIN
#define W5500_INT_PIN 37

static const uint8_t SS = SPI_SS_PIN;
static const uint8_t MOSI = SPI_MOSI_PIN;
static const uint8_t SCK = SPI_MISO_PIN;
static const uint8_t MISO = SPI_SCK_PIN;

// Main I2C Bus (AXP202, BMA423, PCF8563)
#define GROVE_SDA 21
#define GROVE_SCL 22
static const uint8_t SDA = GROVE_SDA;
static const uint8_t SCL = GROVE_SCL;

// Touch I2C Bus (FT6236) - separate I2C
#define TOUCH_SDA 23
#define TOUCH_SCL 32

// TFT_eSPI display
#define USER_SETUP_LOADED
#define ST7789_DRIVER
#define TFT_WIDTH 240
#define TFT_HEIGHT 240
#define CGRAM_OFFSET
#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST -1
#define TFT_BL 12
#define TFT_BACKLIGHT_ON HIGH
#define SMOOTH_FONT 1
#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 6000000

// Display Setup
#define HAS_SCREEN
#define ROTATION 2
#define MINBRIGHT (uint8_t)1

// Font Sizes
#define FP 1
#define FM 2
#define FG 3

// Serial / GPS
#define SERIAL_TX 33
#define SERIAL_RX 34

#define GPS_SERIAL_TX SERIAL_TX
#define GPS_SERIAL_RX SERIAL_RX

#define BAD_TX SERIAL_TX
#define BAD_RX SERIAL_RX

// Buttons & Navigation
#define BTN_ALIAS "\"Mid\""
#define HAS_BTN 1
#define BTN_PIN 36
#define BTN_ACT LOW

// IR pins
#define TXLED 13
#define RXLED 15

#define LED_ON HIGH
#define LED_OFF LOW

// Battery
#define BAT_PIN 34

// Mic (SPM1423 on 2020 V3, otherwise via backplane)
#define PIN_CLK 44
#define PIN_DATA 47

// Backplane pins
#define MOTOR_PIN 4
#define I2S_BCK 26
#define I2S_WS 25
#define I2S_DOUT 33

#endif /* Pins_Arduino_h */