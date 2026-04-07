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

    TimerOption options[3] = {
        {"Option 1", 25, 5},
        {"Option 2", 45, 5},
        {"Option 3", 15, 5}
    };

    int selectedIndex = 0;

public:
    StartScreen(DisplayManager& displayRef);

    void draw() override;
    void update() override;
};