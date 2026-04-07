#include "WorkScreen.h"
#include <Arduino.h>


WorkScreen::WorkScreen(DisplayManager& displayRef)
    : display(displayRef) {}

void WorkScreen::draw() {
    //Serial.println("Drawing Work Screen");
    display.drawCenteredText("Work Screen");
}

void WorkScreen::update() {
    // nothing yet
}