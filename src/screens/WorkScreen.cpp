#include "WorkScreen.h"
#include <Arduino.h>
#include "stdio.h"

WorkScreen::WorkScreen(DisplayManager& displayRef)
    : display(displayRef), selectedIndex(0), progress(0.12), timeText("25 mins") {}

void WorkScreen::draw() {
    //Serial.println("Drawing Work Screen");
    display.drawWorkScreen(timeText, selectedIndex, progress);
}

void WorkScreen::drawFullRefresh() {
    display.fullRefreshWorkScreen(timeText, selectedIndex, progress);
}

void WorkScreen::update() {
    timer.update();

    int remaining = timer.getRemainingSeconds();
    int minutes = remaining / 60;
    int seconds = remaining % 60;
    
    sprintf(timeText, "%d:%02d", minutes, seconds);
    progress = timer.getProgress();
}

void WorkScreen::setSelectedIndex(int index) {
    selectedIndex = index;
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

    snprintf(timeText, sizeof(timeText), "%d:00", workMins);
    progress = 0.0f;
}

void WorkScreen::startTimer() {
    timer.start(workMins * 60);
}