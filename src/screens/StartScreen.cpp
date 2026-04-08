#include <Arduino.h>
#include "StartScreen.h"

StartScreen::StartScreen(DisplayManager& displayRef) 
    : display (displayRef) {}

void StartScreen::draw() {
    //Serial.println("Drawing Start Screen");
    const char* labels[3];
    static char labelBuffers[3][16]; // holds formatted strings
    for (int i = 0; i < 3; i++) {
        sprintf(labelBuffers[i], "%d / %d",
                options[i].workMinutes,
                options[i].breakMinutes);

        labels[i] = labelBuffers[i];
    }

    display.drawStartOptions(labels, 3, selectedIndex);

}

void StartScreen::update() {
    // nothing yet
    // if(selectedIndex changes{
    //     selectedIndex = newIndex;
    //     draw();
    // }
}

void StartScreen::drawFullRefresh() {
    const char* labels[3];
    static char labelBuffers[3][16];

    for (int i = 0; i < 3; i++) {
        sprintf(labelBuffers[i], "%d / %d",
                options[i].workMinutes,
                options[i].breakMinutes);
        labels[i] = labelBuffers[i];
    }

    display.fullRefreshStartScreen(labels, 3, selectedIndex);
}

const TimerOption& StartScreen::getSelectedOption() const {
    return options[selectedIndex];
}