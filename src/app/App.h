//This file defines the main App.cpp class
#pragma once

#include "AppState.h"
#include "display/DisplayManager.h"
#include "screens/StartScreen.h"
#include "screens/WorkScreen.h"
#include "screens/PauseScreen.h"
#include "Stats.h"

class App {
private:
    AppState state;
    DisplayManager display;

    StartScreen startScreen;
    WorkScreen workScreen;
    PauseScreen pauseScreen;
    Stats stats;
    bool lastCycleState = false;
    bool lastSelectState = false;
    bool cyclePressedEvent = false;
    bool selectPressedEvent = false;
    
    void changeState(AppState newState);

public:
    App();
    void init();
    void update();
};