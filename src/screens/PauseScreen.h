#pragma once

#include "Screen.h"
#include "display/DisplayManager.h"

class PauseScreen : public Screen {
private:
    DisplayManager& display;
public:
    PauseScreen(DisplayManager& displayRef);
    void draw() override;
    void update() override;
};