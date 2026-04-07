#include <Arduino.h>
#include "DisplayManager.h"

DisplayManager::DisplayManager()
    : display(GxEPD2_426_GDEQ0426T82(/*CS=*/ 5, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)) {}
// GDEQ0426T82 480x800, SSD1677 (P426010-MF1-A)



void DisplayManager::init() {
    display.init(115200);
    display.setRotation(0);
    //display.clearScreen();
    Serial.println("Display initialized");
}

void DisplayManager::clear() {
    //Serial.println("Display cleared");
    display.setFullWindow();
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
    } while (display.nextPage());
}

void DisplayManager::refresh() {
    //Serial.println("Display refreshed");
}

void DisplayManager::drawCenteredText(const char* text) {
    display.setFullWindow();
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);

        display.setTextColor(GxEPD_BLACK);
        display.setTextSize(2);

        int16_t tbx, tby;
        uint16_t tbw, tbh;
        display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh);

        uint16_t x = (display.width() - tbw) / 2;
        uint16_t y = (display.height() + tbh) / 2;

        display.setCursor(x, y);
        display.print(text);

    } while (display.nextPage());
}

void DisplayManager::drawStartOptions(const char* labels[], int count, int selectedIndex) {
    display.fillScreen(GxEPD_WHITE);

    int boxWidth = display.width() / count;
    int boxHeight = display.height() - 40;

    for (int i = 0; i < count; i++) {
        int x = i * boxWidth;
        int y = 20;

        display.fillRect(x + 5, y, boxWidth - 10, boxHeight, GxEPD_LIGHTGREY);

        if (i == selectedIndex) {
            display.drawRect(x + 5, y, boxWidth - 10, boxHeight, GxEPD_BLACK);
            display.drawRect(x + 6, y + 1, boxWidth - 12, boxHeight - 2, GxEPD_BLACK);
        } else {
            display.drawRect(x + 5, y, boxWidth - 10, boxHeight, GxEPD_BLACK);
        }

        display.setTextColor(GxEPD_BLACK);
        display.setTextSize(1);

        int16_t tbx, tby;
        uint16_t tbw, tbh;
        display.getTextBounds(labels[i], 0, 0, &tbx, &tby, &tbw, &tbh);

        int textX = x + (boxWidth - tbw) / 2;
        int textY = y + boxHeight - 10;

        display.setCursor(textX, textY);
        display.print(labels[i]);
    }

    display.display(false);
    Serial.println("Done Drawing Start Screen");
}