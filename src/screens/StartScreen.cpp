#include <Arduino.h>
#include "StartScreen.h"

StartScreen::StartScreen(DisplayManager& displayRef) 
    : display (displayRef) {}

void StartScreen::draw() {
    Serial.println("Drawing Start Screen");
        const char* labels[3] = {
        "25 / 5",
        "45 / 5",
        "15 / 5"
    };

    display.drawStartOptions(labels, 3, selectedIndex);

}

void StartScreen::update() {
    // nothing yet
}