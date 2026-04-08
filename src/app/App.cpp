//This file sets the initial state and controls the behavior of the app
#include <Arduino.h>
#include "App.h"

static unsigned long startTime = millis();

App::App() 
    : state(AppState::Start),
    display(),
    startScreen(display),
    workScreen(display),
    pauseScreen(display) {}

void App::init() {
   Serial.begin(115200);
   delay(1000);
    startTime = millis();

   //Serial.println("App init");
   display.init();
   changeState(AppState::Start);    
}

//runs when switching screens
void App::changeState(AppState newState){

    state = newState;

    switch (state) {
        case AppState::Start: {
            //startScreen.drawFullRefresh();
            startScreen.draw();
            break;
        }
           
        case AppState::Work: {
            const TimerOption& selected = startScreen.getSelectedOption();
            workScreen.setTimerVals(selected.workMinutes, selected.breakMinutes);
            workScreen.startTimer();
            // workScreen.drawFullRefresh();
            workScreen.draw();
            break;
        }
           
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
            if(millis() - startTime > 10000){
                changeState(AppState::Work);}
            break;

        case AppState::Work:
            workScreen.update();
            workScreen.draw();
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
