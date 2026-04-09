#include "Stats.h"
#include <Arduino.h>

void Stats::startSession(bool isBreak) {
    sessionIsBreak = isBreak;
    sessionRunning = true;
    currentSessionSeconds = 0;
    lastUpdateMillis = millis();
}

void Stats::pauseSession() {
    update();
    sessionRunning = false;
}

void Stats::resumeSession() {
    sessionRunning = true;
    lastUpdateMillis = millis();
}

void Stats::update() {
    if (!sessionRunning) return;

    unsigned long now = millis();
    unsigned long elapsedMs = now - lastUpdateMillis;
    unsigned long elapsedSeconds = elapsedMs / 1000;

    if (elapsedSeconds > 0) {
        lastUpdateMillis += elapsedSeconds * 1000;
        currentSessionSeconds += elapsedSeconds;

        if (sessionIsBreak) {
            breakTodaySeconds += elapsedSeconds;
        } else {
            workTodaySeconds += elapsedSeconds;
        }
    }
}

unsigned long Stats::getWorkToday() const {
    return workTodaySeconds;
}

unsigned long Stats::getBreakToday() const {
    return breakTodaySeconds;
}

unsigned long Stats::getSessionTime() const {
    return currentSessionSeconds;
}