#pragma once

#include "Screen.h"
#include "display/DisplayManager.h"
#include "timer/Timer.h"

class WorkScreen : public Screen {
private:
    DisplayManager& display;
    Timer timer;

    int workMins = 25;
    int breakMins = 5;
    int selectedIndex = 0;
    float progress = 0.0f;
    //const char* timeText = "25 minutes";
    char timeText[20] = "25:00";

public:
    WorkScreen(DisplayManager& displayRef);

    void draw() override;
    void update() override;

    void drawFullRefresh();
    void setSelectedIndex(int index);
    void setProgress(float value);
    void setTimeText(const char* text);
    void setTimerVals(int work, int rest);

    void startTimer();
};