#pragma once

class Stats {
public:
    void startSession(bool isBreak);
    void pauseSession();
    void resumeSession();
    void update();

    unsigned long getWorkToday() const;
    unsigned long getBreakToday() const;
    unsigned long getSessionTime() const;

private:
    unsigned long workTodaySeconds = 0;
    unsigned long breakTodaySeconds = 0;
    unsigned long currentSessionSeconds = 0;

    bool sessionRunning = false;
    bool sessionIsBreak = false;

    unsigned long lastUpdateMillis = 0;
};