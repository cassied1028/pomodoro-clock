#include "Timer.h"
#include <Arduino.h>

void Timer::start(int seconds) {
    totalSeconds = seconds;
    remainingSeconds = seconds;
    startMillis = millis();
    pausedMillis = 0;

    running = true;
    paused = false;
}

void Timer::update() {
    if (!running || paused) {
        return;
    }

    unsigned long elapsedSeconds = (millis() - startMillis) / 1000;
    remainingSeconds = totalSeconds - (int)elapsedSeconds;

    if (remainingSeconds <= 0) {
        remainingSeconds = 0;
        running = false;
    }
}

void Timer::pause() {
    if (!running || paused) {
        return;
    }

    pausedMillis = millis();
    paused = true;
}

void Timer::resume() {
    if (!running || !paused) {
        return;
    }

    unsigned long pauseDuration = millis() - pausedMillis;
    startMillis += pauseDuration;
    paused = false;
}

void Timer::stop() {
    totalSeconds = 0;
    remainingSeconds = 0;
    startMillis = 0;
    pausedMillis = 0;

    running = false;
    paused = false;
}

int Timer::getRemainingSeconds() const {
    return remainingSeconds;
}

float Timer::getProgress() const {
    if (totalSeconds <= 0) {
        return 0.0f;
    }

    return 1.0f - ((float)remainingSeconds / (float)totalSeconds);
}

bool Timer::isRunning() const {
    return running;
}

bool Timer::isFinished() const {
    return (!running && remainingSeconds == 0 && totalSeconds > 0);
}