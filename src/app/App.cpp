//This file sets the initial state and controls the behavior of the app
#include <Arduino.h>
#include "App.h"

static unsigned long startTime = 0;
bool cyclePressedEvent = false;
bool selectPressedEvent = false;

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
   pinMode(14, INPUT_PULLUP);
   pinMode(12, INPUT_PULLUP);

   //Serial.println("App init");
   display.init();
   startScreen.drawFullRefresh();
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
    bool cycleButtonPress = digitalRead(14) == LOW;
    bool selectButtonPress = digitalRead(12) == LOW;

    //making buttons sticky
    if (cycleButtonPress && !lastCycleState) {
        cyclePressedEvent = true;
    }

    if (selectButtonPress && !lastSelectState) {
        selectPressedEvent = true;
    }

    switch (state) {
        case AppState::Start:
            
            if(cyclePressedEvent){
                startScreen.nextOption();
                Serial.println("cycle button pressed");}
                cyclePressedEvent = false;
            if(selectPressedEvent && !lastSelectState){
                Serial.println("select button pressed");
                selectPressedEvent = false;
                changeState(AppState::Work);}
                
            // if(millis() - startTime > 10000){
            //     changeState(AppState::Work);}
            startScreen.update();
            break;

        case AppState::Work:
            if(cyclePressedEvent){
                workScreen.nextOption();
                cyclePressedEvent = false;
                Serial.println("cycle button pressed");}
            if(selectPressedEvent && workScreen.getSelectedIndex() == 2){
                Serial.println("select button pressed");
                selectPressedEvent = false;
                changeState(AppState::Start);}
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
    lastCycleState = cycleButtonPress;
    lastSelectState = selectButtonPress;
}
