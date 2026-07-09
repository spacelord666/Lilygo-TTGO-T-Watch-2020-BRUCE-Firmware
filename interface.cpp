#include "core/powerSave.h"
#include "core/utils.h"
#include <Wire.h>
#include <XPowersLib.h>
#include <interface.h>

XPowersAXP202 axp202;
#include <TouchDrvFT6X36.hpp>
TouchDrvFT6X36 touch;

static bool touch_available = false;

/***************************************************************************************
** Function name: _setup_gpio()
** Description:   initial setup for the device
***************************************************************************************/
void _setup_gpio() {
    Wire.begin(21, 22);
    delay(10);

    if (!axp202.init(Wire, 21, 22, AXP202_SLAVE_ADDRESS)) {
        Serial.println("AXP202 PMU not found!");
    } else {
        axp202.disableIRQ(XPOWERS_AXP202_ALL_IRQ);
        axp202.enableIRQ(XPOWERS_AXP202_VBUS_REMOVE_IRQ | XPOWERS_AXP202_VBUS_INSERT_IRQ |
                         XPOWERS_AXP202_BAT_REMOVE_IRQ | XPOWERS_AXP202_BAT_INSERT_IRQ |
                         XPOWERS_AXP202_BAT_CHG_DONE_IRQ | XPOWERS_AXP202_BAT_CHG_START_IRQ);
        axp202.clearIrqStatus();

        axp202.setChargingLedMode(XPOWERS_CHG_LED_CTRL_CHG);
        axp202.setLDO2Voltage(3300);
        axp202.setLDO3Voltage(3300);

        axp202.enableLDO2();
        axp202.enableLDO3();

        pinMode(TOUCH_SDA, INPUT_PULLUP);
        pinMode(TOUCH_SCL, INPUT_PULLUP);
        Wire1.begin(TOUCH_SDA, TOUCH_SCL);
        delay(10);

        if (touch.begin(Wire1, FT6X36_SLAVE_ADDRESS, TOUCH_SDA, TOUCH_SCL)) {
            touch.setSwapXY(true);
            touch.interruptPolling();
            touch_available = true;
        } else {
            Wire1.end();
        }
    }

    pinMode(BTN_PIN, INPUT_PULLUP);

    bruceConfigPins.rfModule = CC1101_SPI_MODULE;
    bruceConfigPins.rfidModule = PN532_I2C_MODULE;

    bruceConfigPins.irRx = RXLED;
    bruceConfigPins.irTx = TXLED;

    Serial.begin(115200);
}

/***************************************************************************************
** Function name: _post_setup_gpio()
** Description:   second stage gpio setup
***************************************************************************************/
void _post_setup_gpio() {
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
}

/***************************************************************************************
** Function name: getBattery()
** Description:   Delivers the battery value from 1-100
***************************************************************************************/
int getBattery() {
    int pct = axp202.getBatteryPercent();
    return (pct < 0) ? 0 : pct;
}

/*********************************************************************
** Function: setBrightness
** set brightness value
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    if (brightval == 0) {
        analogWrite(TFT_BL, 0);
    } else {
        int bl = MINBRIGHT + round(((255 - MINBRIGHT) * brightval / 100));
        analogWrite(TFT_BL, bl);
    }
}

/*********************************************************************
** Function: InputHandler
** Handles the variables PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
**********************************************************************/
void InputHandler(void) {
    static unsigned long tm = 0;

    if (millis() - tm > 200 || LongPress) {
        int16_t tx = 0, ty = 0;

        if (touch_available && touch.getPoint(&tx, &ty)) {
            if (bruceConfigPins.rotation == 2) {
                ty = (tftHeight + 20) - ty;
            }
            if (bruceConfigPins.rotation == 3) {
                int tmp = tx;
                tx = tftWidth - ty;
                ty = tftHeight - tmp;
            }
            if (bruceConfigPins.rotation == 1) {
                int tmp = tx;
                tx = ty;
                ty = tmp;
            }
            if (bruceConfigPins.rotation == 0) {
                tx = tftWidth - tx;
            }

            if (!wakeUpScreen()) AnyKeyPress = true;
            else return;

            touchPoint.x = tx;
            touchPoint.y = ty;
            touchPoint.pressed = true;
            touchHeatMap(touchPoint);

            tm = millis();
        }

        if (digitalRead(BTN_PIN) == LOW) {
            if (!wakeUpScreen()) AnyKeyPress = true;
            else return;
            SelPress = true;
            tm = millis();
        }
    }
}

/*********************************************************************
** Function: powerOff
** Turns off the device
**********************************************************************/
void powerOff() {
    tft.fillScreen(TFT_BLACK);
    digitalWrite(TFT_BL, LOW);
    tft.writecommand(0x10);
    esp_sleep_enable_ext0_wakeup((gpio_num_t)BTN_PIN, LOW);
    esp_deep_sleep_start();
}

/*********************************************************************
** Function: checkReboot
** Btn logic to turn off the device
**********************************************************************/
void checkReboot() {
    if (digitalRead(BTN_PIN) == LOW) {
        uint32_t time_count = millis();
        while (digitalRead(BTN_PIN) == LOW) {
            if (millis() - time_count > 2000) {
                int textWidth = tft.textWidth("PWR OFF IN 3/3", 1);
                tft.fillRect(tftWidth / 2 - textWidth / 2, 7, textWidth, 18, bruceConfig.bgColor);
                tft.setTextSize(1);
                tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
                int countDown = (millis() - time_count) / 1000 + 1;
                if (countDown < 4) {
                    tft.drawCentreString("PWR OFF IN " + String(countDown) + "/3", tftWidth / 2, 12, 1);
                } else {
                    tft.fillScreen(bruceConfig.bgColor);
                    while (digitalRead(BTN_PIN) == LOW);
                    delay(200);
                    powerOff();
                }
                delay(10);
            }
        }
        delay(30);
        if (millis() - time_count > 500) {
            tft.fillRect(60, 12, tftWidth - 60, tft.fontHeight(1), bruceConfig.bgColor);
            drawStatusBar();
        }
    }
}

/***************************************************************************************
** Function name: isCharging()
** Description:   Returns charging status
***************************************************************************************/
bool isCharging() {
    return axp202.isCharging();
}