#pragma once

#include "Screen.h"
#include "display/DisplayManager.h"

struct TimerOption {
    const char* label;
    int workMinutes;
    int breakMinutes;
};

class StartScreen : public Screen {
private:
    DisplayManager& display;

    //CHANGE WORKING TIMES HERE
    TimerOption options[3] = {
        {"Option 1", 5, 5},
        {"Option 2", 45, 10},
        {"Option 3", 60, 15}
    };

    int selectedIndex = 0;

public:
    StartScreen(DisplayManager& displayRef);

    void draw() override;
    void update() override;
    void nextOption();
    void prevOption();
    void drawFullRefresh();
    int getSpriteIndex();

    const TimerOption& getSelectedOption() const;
};