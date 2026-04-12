#include "WorkScreen.h"
#include <Arduino.h>
#include "stdio.h"

WorkScreen::WorkScreen(DisplayManager& displayRef)
    : display(displayRef), selectedIndex(0), progress(0.12), timeText("25 mins"), lastDisplayedMinute(-1) {}

void WorkScreen::draw() {
    //Serial.println("Drawing Work Screen");
    display.drawWorkScreen(timeText, selectedIndex, progress, spriteIndex, isOnBreak());
}

// void WorkScreen::drawFullRefresh() {
//     display.fullRefreshWorkScreen(timeText, selectedIndex, progress);
// }

void WorkScreen::update() {
    timer.update();

    int remaining = timer.getRemainingSeconds();
    int minutes = (remaining + 59) / 60;
    int seconds = remaining % 60;
    progress = timer.getProgress();
    
    if(remaining == 0 && !timeFinished){
        if(onBreak){snprintf(timeText, sizeof(timeText), "Time to Work!");}
        else{snprintf(timeText, sizeof(timeText), "Time for Break!");}
        timeFinished = true;
        draw();
    }else if(remaining < 60 && remaining > 0 && seconds != lastDisplayedSecond){
        lastDisplayedSecond = seconds;
        if(onBreak){sprintf(timeText, "%d break secs", seconds);}
        else{sprintf(timeText, "%d secs", seconds);}
        draw();
    }else if (minutes != lastDisplayedMinute && remaining > 0) {
        lastDisplayedMinute = minutes;
        if(onBreak){
            sprintf(timeText, "%d min break", minutes);
        }else{
            sprintf(timeText, "%d mins", minutes);
        } 
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

void WorkScreen::prevOption(){
    selectedIndex = (selectedIndex - 1 + 3) % 3;
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
    onBreak = false;
    timeFinished = false;
    lastDisplayedMinute = -1;
    timer.start(workMins * 60);
}

void WorkScreen::startBreakTimer() {
    onBreak = true;
    timeFinished = false;
    timer.start(breakMins * 60);
    lastDisplayedMinute = -1;
}

void WorkScreen::setSpriteIndex(int index) {
    spriteIndex = index;
}

bool WorkScreen::isOnBreak(){
    return onBreak;
}