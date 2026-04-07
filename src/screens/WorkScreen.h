#pragma once

#include "Screen.h"
#include "display/DisplayManager.h"

class WorkScreen : public Screen {
private:
    DisplayManager& display;

public:
    WorkScreen(DisplayManager& displayRef);

    void draw() override;
    void update() override;
};