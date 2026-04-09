//This file sets the initial state and controls the behavior of the app
#include <Arduino.h>
#include "App.h"
#include "Stats.h"

static unsigned long startTime = 0;


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
            // const TimerOption& selected = startScreen.getSelectedOption();
            // workScreen.setTimerVals(selected.workMinutes, selected.breakMinutes);
            // workScreen.setSpriteIndex(startScreen.getSpriteIndex());
            // Serial.println(startScreen.getSpriteIndex());
            // workScreen.startTimer();
            // stats.startSession(false);
            // // workScreen.drawFullRefresh();
            workScreen.draw();
            break;
        }
           
        case AppState::Break:
            break;

        case AppState::Pause:
            stats.pauseSession();
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
    stats.update();
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
                cyclePressedEvent = false;}
            if(selectPressedEvent){
                const TimerOption& selected = startScreen.getSelectedOption();
                workScreen.setTimerVals(selected.workMinutes, selected.breakMinutes);
                workScreen.setSpriteIndex(startScreen.getSpriteIndex());
                workScreen.startTimer();
                stats.startSession(false);
                selectPressedEvent = false;
                changeState(AppState::Work);
            }
            //startScreen.update();
            break;

        case AppState::Work:
            if(cyclePressedEvent){
                workScreen.nextOption();
                cyclePressedEvent = false;
                }
            if(selectPressedEvent){
                if(workScreen.getSelectedIndex() == 0){
                    pauseScreen.setPausedMinutesRemaining((workScreen.getSeconds()+59) / 60);
                    Serial.print("Work Today: ");
                    Serial.print(stats.getWorkToday());
                    Serial.print("s | Break Today: ");
                    Serial.print(stats.getBreakToday());
                    Serial.print("s | Session: ");
                    Serial.print(stats.getSessionTime());
                    Serial.println("s");
                    pauseScreen.setStats(
                        stats.getWorkToday(),
                        stats.getBreakToday(),
                        stats.getSessionTime()
                    );                    
                    changeState(AppState::Pause);
                }else if (workScreen.getSelectedIndex() == 1){
                    if(workScreen.isOnBreak()){
                        stats.startSession(false);
                        workScreen.startTimer();
                    }else{
                        stats.startSession(true);
                        workScreen.startBreakTimer();
                    }
                    
                }else if(workScreen.getSelectedIndex() ==2){
                    changeState(AppState::Start);
                }
                selectPressedEvent = false;
            }
            workScreen.update();

            break;

        case AppState::Pause:
            if(cyclePressedEvent){
                pauseScreen.nextOption();
                cyclePressedEvent = false;
            }
            if(selectPressedEvent){
                if(pauseScreen.getSelectedIndex() == 0){
                    stats.resumeSession();
                    changeState(AppState::Work);
                }else if (pauseScreen.getSelectedIndex() == 2){
                    changeState(AppState::Start);
                }
                selectPressedEvent = false;
            }
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