// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>
#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
GxEPD2_BW<GxEPD2_426_GDEQ0426T82, GxEPD2_426_GDEQ0426T82::HEIGHT> display(GxEPD2_426_GDEQ0426T82(/*CS=5*/ 5, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEQ0426T82 480x800, SSD1677 (P426010-MF1-A)

void setup()
{
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  drawStaticScreen("Work!");
  for(int i=10; i>=0; i--){
    char numStr[4];
    sprintf(numStr, "%d", i);
    drawNumbers(numStr);
    delay(1000);
  }
  drawStaticScreen("Take a break...");
  delay(3000);
  for(int i=5; i>=0; i--){
    char numStr[4];
    sprintf(numStr, "%d", i);
    drawNumbers(numStr);
    delay(1000);
  }
  display.hibernate(); //low power mode after drawing
}

void drawStaticScreen(char Title[])
{
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();//update entire display area
  display.firstPage();

  do{
    display.fillScreen(GxEPD_WHITE);
    //Title
    display.setFont(&FreeMonoBold18pt7b);
    int16_t tbx, tby; 
    uint16_t tbw, tbh; 
    display.getTextBounds(Title, 0, 0, &tbx, &tby, &tbw, &tbh); //telling how much space the text would take up
    uint16_t titlex = ((display.width() - tbw) / 2) - tbx;
    uint16_t titley = ((display.height() - tbh) / 4) - tby;

    display.setCursor(titlex, titley);
    display.print(Title);
  } while (display.nextPage());
}

void drawNumbers(const char* numStr){
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold24pt7b);
  int16_t tbx, tby; 
  uint16_t tbw, tbh; 
  display.getTextBounds(numStr, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t numx = ((display.width() - tbw) / 2) - tbx;
  uint16_t numy = ((display.height() - tbh) / 2) - tby;

  //box for timer
  display.setPartialWindow(150, 140, 500, 180);
  display.firstPage();

  do{
    display.fillScreen(GxEPD_WHITE); //clear partial window
    display.setCursor(numx, numy);
    display.print(numStr);
  }while(display.nextPage());

}


void loop() {};

