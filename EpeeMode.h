// EpeeMode.h - Epee-specific configuration and rules
#ifndef EPEEMODE_H
#define EPEEMODE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <Scorebox.h>

using namespace std;
// EpeeMode class definition
// EpeeMode.h - Epee-specific configuration and rules



class EpeeMode {
private:
    Scorebox* scorebox;
    int lockoutTime = 3000; // The time in milliseconds to lock out after a hit
    bool isLocked = false;
    bool redHit = false;
    bool greenHit = false;

public:
    EpeeMode(Scorebox* sb);
    void evaluateHit();
    void groundingCheck();
};

#endif