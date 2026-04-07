#pragma once

class Timer{
private:
    int totalSeconds = 0;
    int remainingSeconds = 0;
    unsigned long startMillis = 0;
    unsigned long pausedMillis = 0;

    bool running = false;
    bool paused = false;
public:
    void start(int seconds);
    void update();
    void pause();
    void resume();
    void stop();

    int getRemainingSeconds() const;
    float getProgress() const;
    bool isRunning() const;
    bool isFinished() const;
};