#include <Arduino.h>
#include "DisplayManager.h"
#include "sprites.h"

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

    int boxWidth = 250;
    int boxHeight = 327;
    int spacing = 20;
    int totalWidth = (count * boxWidth) + ((count - 1) * spacing);
    int startX = (display.width() - totalWidth) / 2;
    int startY = (display.height() - boxHeight) / 2;

    for (int i = 0; i < count; i++) {
        int x = startX + i * (boxWidth + spacing);
        int y = startY;

        display.fillRect(x, y, boxWidth, boxHeight, GxEPD_WHITE);
        
        if (i == selectedIndex) {
            // Thicker (double rounded border)
            display.drawRoundRect(x, y, boxWidth, boxHeight, 12, GxEPD_BLACK);
            display.drawRoundRect(x + 2, y + 2, boxWidth - 4, boxHeight - 4, 12, GxEPD_BLACK);
        } else {
            display.drawRoundRect(x, y, boxWidth, boxHeight, 12, GxEPD_BLACK);
        }
         
        display.setTextColor(GxEPD_BLACK);
        display.setTextSize(3);

        int16_t tbx, tby;
        uint16_t tbw, tbh;
        display.getTextBounds(labels[i], 0, 0, &tbx, &tby, &tbw, &tbh);

        int textX = x + (boxWidth - tbw) / 2;
        int textY = y + boxHeight - 30;

        display.setCursor(textX, textY);
        display.print(labels[i]);

        if(i == 0){
            int imgX = x + (boxWidth - TURTWIG_WIDTH) / 2;
            int imgY = y + (boxHeight - TURTWIG_HEIGHT) / 2;
            display.fillRect(imgX, imgY, TURTWIG_WIDTH, TURTWIG_HEIGHT, GxEPD_WHITE);
            display.drawBitmap(imgX, imgY,turtwigBitmapsprite_2_1_icon,
                    TURTWIG_WIDTH, TURTWIG_HEIGHT, GxEPD_BLACK);
        }
        else if(i == 1){
            int imgX = x + (boxWidth - PIPLUP_WIDTH) / 2;
            int imgY = y + (boxHeight - PIPLUP_HEIGHT) / 2;
            display.fillRect(imgX, imgY, PIPLUP_WIDTH, PIPLUP_HEIGHT, GxEPD_WHITE);
            display.drawBitmap(imgX, imgY,piplupBitmapsprite_2_19_icon,
                    PIPLUP_WIDTH, PIPLUP_HEIGHT, GxEPD_BLACK);
        }else{
            int imgX = x + (boxWidth - CHIMCHAR_WIDTH) / 2;
            int imgY = y + (boxHeight - CHIMCHAR_HEIGHT) / 2;
            display.fillRect(imgX, imgY, CHIMCHAR_WIDTH, CHIMCHAR_HEIGHT, GxEPD_WHITE);
            display.drawBitmap(imgX, imgY,chimcharBitmapsprite_2_10_icon,
                    CHIMCHAR_WIDTH, CHIMCHAR_HEIGHT, GxEPD_BLACK);
        }
   
    }
    //change to false for quicker refresh
    display.display(true);
    
    Serial.println("Done Drawing Start Screen");
}