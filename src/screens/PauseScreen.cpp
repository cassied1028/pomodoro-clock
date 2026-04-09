#include <Arduino.h>
#include "PauseScreen.h"
#include "display/DisplayManager.h"

PauseScreen::PauseScreen(DisplayManager& displayRef)
    : display(displayRef){}

void PauseScreen::draw() {
    display.drawPauseScreen(
        selectedIndex,
        pausedMinutesRemaining,
        workTodayMinutes,
        breakTodayMinutes,
        sessionMinutes
    );
}

void PauseScreen::update() {
    // nothing yet
}

void PauseScreen::nextOption() {
    if (selectedIndex == 0) {
        selectedIndex = 2;
    } else {
        selectedIndex = 0;
    }
    draw();
}

void PauseScreen::setSelectedIndex(int index) {
    selectedIndex = index;
}

int PauseScreen::getSelectedIndex() {
    return selectedIndex;
}

void PauseScreen::setPausedMinutesRemaining(int mins) {
    pausedMinutesRemaining = mins;
}

void PauseScreen::setStats(int workToday, int breakToday, int sessionTime) {
    workTodayMinutes = workToday;
    breakTodayMinutes = breakToday;
    sessionMinutes = sessionTime;
}