// EpeeMode.h - Epee-specific configuration and rules
#ifndef EPEEMODE_H
#define EPEEMODE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "Scorebox.h"

using namespace std;
// EpeeMode class definition
// EpeeMode.h - Epee-specific configuration and rules



class EpeeMode {
private:
    Scorebox* scorebox;
    int targetScore;        // Points needed to win (typically 15)
    int maxTime;           // Maximum bout time in seconds
    unsigned long boutStartTime;
    bool boutActive;
    
public:
    EpeeMode(Scorebox* sb);
    void startBout();
    void endBout();
    bool checkWinCondition();
    void displayBoutStatus();
    int getTimeRemaining();
    void resetScores();
};

#endif