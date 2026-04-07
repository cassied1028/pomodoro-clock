#include <Arduino.h>
#include "app/App.h"

App app;

void setup() {
    app.init();
}

void loop() {
    app.update();
}