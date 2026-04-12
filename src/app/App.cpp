//This file sets the initial state and controls the behavior of the app
#include <Arduino.h>
#include "App.h"
#include "Stats.h"

static unsigned long startTime = 0;

// RGB LED pins
const int RED_PIN = 13;
const int GREEN_PIN = 12;
const int BLUE_PIN = 14;
// PWM channels
const int RED_CH = 0;
const int GREEN_CH = 1;
const int BLUE_CH = 2;

// Rotary encoder pins
const int ENC_CLK = 27;
const int ENC_DT  = 26;
const int ENC_SW  = 25;
// Encoder state
bool nextEvent = false;
bool prevEvent = false;
int lastClkState = HIGH;
bool lastSwState = HIGH;

void setColor(int r, int g, int b) {
    ledcWrite(RED_CH, r);
    ledcWrite(GREEN_CH, g);
    ledcWrite(BLUE_CH, b);
}

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

    // RGB LED setup
   ledcSetup(RED_CH, 5000, 8);
   ledcSetup(GREEN_CH, 5000, 8);
   ledcSetup(BLUE_CH, 5000, 8);
   ledcAttachPin(RED_PIN, RED_CH);
   ledcAttachPin(GREEN_PIN, GREEN_CH);
   ledcAttachPin(BLUE_PIN, BLUE_CH);
   setColor(0, 0, 0); // start off

    // Rotary encoder setup
   pinMode(ENC_CLK, INPUT_PULLUP);
   pinMode(ENC_DT, INPUT_PULLUP);
   pinMode(ENC_SW, INPUT_PULLUP);
   lastClkState = digitalRead(ENC_CLK);
   lastSwState = digitalRead(ENC_SW);

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
            setColor(0, 0, 0);
            startScreen.draw();
            break;
        }
           
        case AppState::Work: {
            workScreen.draw();
            break;
        }
           
        case AppState::Break:
            setColor(0, 255, 0);
            break;

        case AppState::Pause:
            setColor(0, 0, 255);
            stats.pauseSession();
            pauseScreen.draw(); 
            break;

        case AppState::End:
            setColor(0, 0, 0);    
            break;
    }
}

//continuosly runs and checks what state to be in currently
void App::update() {
    stats.update();
    // --- Rotary movement detection ---
    int clkState = digitalRead(ENC_CLK);

    if (clkState != lastClkState && clkState == LOW) {
        if (digitalRead(ENC_DT) != clkState) {
            nextEvent = true;   // clockwise
        } else {
            prevEvent = true;   // counterclockwise
        }
    }
    lastClkState = clkState;

    // --- Encoder button press detection ---
    bool swState = digitalRead(ENC_SW);

    if (swState == LOW && lastSwState == HIGH) {
        selectPressedEvent = true;
    }
    lastSwState = swState;

    switch (state) {
        case AppState::Start:
             setColor(0, 0, 0);
            if(nextEvent){
                startScreen.nextOption();
                nextEvent = false;}
            if(prevEvent){
                startScreen.prevOption();
                prevEvent = false;
            }
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
            if(nextEvent){
                workScreen.nextOption();
                nextEvent = false;}
            if(prevEvent){
                workScreen.prevOption();
                prevEvent = false;
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
                        setColor(255,0, 0);
                        stats.startSession(false);
                        workScreen.startTimer();
                    }else{
                        setColor(0, 255, 0);
                        stats.startSession(true);
                        workScreen.startBreakTimer();
                    }
                    
                }else if(workScreen.getSelectedIndex() ==2){
                    changeState(AppState::Start);
                }
                selectPressedEvent = false;
            }

            if(workScreen.isOnBreak()){setColor(0,255, 0);
            }else{setColor(255,0, 0);}

            workScreen.update();

            break;

        case AppState::Pause:
            if(nextEvent){
                pauseScreen.nextOption();
                nextEvent = false;
            }
            if(prevEvent){
                pauseScreen.nextOption();
                prevEvent = false;
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
            setColor(0,0,255);
            pauseScreen.update();
            break;

        case AppState::Break:
            break;

        case AppState::End:
            break;
    }
}