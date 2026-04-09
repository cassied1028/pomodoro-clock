#include "WorkScreen.h"
#include <Arduino.h>
#include "stdio.h"

WorkScreen::WorkScreen(DisplayManager& displayRef)
    : display(displayRef), selectedIndex(0), progress(0.12), timeText("25 mins"), lastDisplayedMinute(-1) {}

void WorkScreen::draw() {
    //Serial.println("Drawing Work Screen");
    display.drawWorkScreen(timeText, selectedIndex, progress);
}

// void WorkScreen::drawFullRefresh() {
//     display.fullRefreshWorkScreen(timeText, selectedIndex, progress);
// }

void WorkScreen::update() {
    timer.update();

    int remaining = timer.getRemainingSeconds();
    int minutes = remaining / 60;
    int seconds = remaining % 60;
    
    sprintf(timeText, "%d mins", minutes, seconds);
    progress = timer.getProgress();
    if (minutes != lastDisplayedMinute) {
        lastDisplayedMinute = minutes;
        draw();
    }
}

int WorkScreen::getSeconds(){
    return timer.getRemainingSeconds();
}

void WorkScreen::setSelectedIndex(int index) {
    selectedIndex = index;
}

int WorkScreen::getSelectedIndex() {
    return selectedIndex;
}

void WorkScreen::nextOption() {
    selectedIndex = (selectedIndex + 1) % 3;
    draw();
}

void WorkScreen::setProgress(float value) {
    if (value < 0.0f) value = 0.0f;
    if (value > 1.0f) value = 1.0f;
    progress = value;
}

void WorkScreen::setTimeText(const char* text) {
    //timeText = text;
    snprintf(timeText, sizeof(timeText), "%s", text);   
}

void WorkScreen::setTimerVals(int work, int rest) {
    workMins = work;
    breakMins = rest;

    snprintf(timeText, sizeof(timeText), "%d mins", workMins);
    progress = 0.0f;
}

void WorkScreen::startTimer() {
    lastDisplayedMinute = -1;
    timer.start(workMins * 60);
}