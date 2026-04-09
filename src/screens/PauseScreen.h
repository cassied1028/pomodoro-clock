#include "display/DisplayManager.h"

class PauseScreen {
public:
    PauseScreen(DisplayManager& displayRef);

    void draw();
    void update();

    void setSelectedIndex(int index);
    int getSelectedIndex();
    void nextOption();

    void setPausedMinutesRemaining(int mins);
    void setStats(int workToday, int breakToday, int sessionTime);

private:
    DisplayManager& display;
    int selectedIndex = 0;

    int pausedMinutesRemaining = 0;
    int workTodayMinutes = 0;
    int breakTodayMinutes = 0;
    int sessionMinutes = 0;
};