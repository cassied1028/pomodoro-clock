#pragma once

#include "Screen.h"
#include "display/DisplayManager.h"
#include "timer/Timer.h"

class WorkScreen : public Screen {
private:
    DisplayManager& display;
    Timer timer;

    int spriteIndex = 0;
    int workMins = 25;
    int breakMins = 5;
    int selectedIndex = 0;
    float progress = 0.0f;
    int lastDisplayedMinute = -1;
    int lastDisplayedSecond = -1;
    bool onBreak = false;
    bool timeFinished = false;
    //const char* timeText = "25 minutes";
    char timeText[20] = "25 mins";

public:
    WorkScreen(DisplayManager& displayRef);

    void draw() override;
    void update() override;
    void setSpriteIndex(int index);

    // void drawFullRefresh();
    void setSelectedIndex(int index);
    void setProgress(float value);
    void setTimeText(const char* text);
    void setTimerVals(int work, int rest);
    void nextOption();
    int getSelectedIndex();
    int getSeconds();

    void startTimer();
    void startBreakTimer();
    bool isOnBreak();
};