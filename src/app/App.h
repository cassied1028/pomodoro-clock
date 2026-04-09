//This file defines the main App.cpp class
#pragma once

#include "AppState.h"
#include "display/DisplayManager.h"
#include "screens/StartScreen.h"
#include "screens/WorkScreen.h"
#include "screens/PauseScreen.h"

class App {
private:
    AppState state;
    DisplayManager display;

    StartScreen startScreen;
    WorkScreen workScreen;
    PauseScreen pauseScreen;
    bool lastCycleState = false;
    bool lastSelectState = false;

    void changeState(AppState newState);

public:
    App();
    void init();
    void update();
};