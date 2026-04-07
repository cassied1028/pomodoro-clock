//This file sets the initial state and controls the behavior of the app
#include <Arduino.h>
#include "App.h"

App::App() 
    : state(AppState::Start),
    display(),
    startScreen(display),
    workScreen(display),
    pauseScreen(display) {}

void App::init() {
   Serial.begin(115200);
   delay(1000);

   Serial.println("App init");
   display.init();
   changeState(AppState::Start);
}

//runs when switching screens
void App::changeState(AppState newState){
    state = newState;

    switch (state) {
        case AppState::Start:
            startScreen.draw();
            break;

        case AppState::Work:
            workScreen.draw();
            break;

        case AppState::Break:
            break;

        case AppState::Pause:
            pauseScreen.draw(); 
            break;

        case AppState::End:
            break;
    }
}

//continuosly runs and checks what state to be in currently
void App::update() {
    switch (state) {
        case AppState::Start:
            startScreen.update();
            break;

        case AppState::Work:
            workScreen.update();
            break;

        case AppState::Pause:
            pauseScreen.update();
            break;

        case AppState::Break:
            break;

        case AppState::End:
            break;
    }
}
