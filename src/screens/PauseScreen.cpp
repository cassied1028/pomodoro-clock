#include <Arduino.h>
#include "PauseScreen.h"

PauseScreen::PauseScreen(DisplayManager& displayRef)
    : display(displayRef){}

void PauseScreen::draw() {
    //Serial.println("Drawing Pause Screen");
    display.drawCenteredText("Pause Screen");

}

void PauseScreen::update() {
    // nothing yet
}