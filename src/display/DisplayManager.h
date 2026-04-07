#pragma once
#include <GxEPD2_BW.h>

class DisplayManager {
private:
    GxEPD2_BW<GxEPD2_426_GDEQ0426T82, GxEPD2_426_GDEQ0426T82::HEIGHT> display;
public:
    DisplayManager();
    void init();
    void clear();
    void refresh();

    void drawCenteredText(const char* text);
    void drawStartOptions(const char* labels[], int count, int selectedIndex);
    void drawWorkScreen(const char* timeText, int selectedIndex, float progress);
    void fullRefreshWorkScreen(const char* timeText, int selectedIndex, float progress);
    void fullRefreshStartScreen(const char* labels[], int count, int selectedIndex);
};