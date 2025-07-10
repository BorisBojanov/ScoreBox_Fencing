// EpeeMode.h - Epee-specific configuration and rules
#ifndef EPEEMODE_H
#define EPEEMODE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <string>
#include <chrono>
#include <thread>
#include <Scorebox.h>
#include <GPIO_Manager.h>

using namespace std;
// EpeeMode class definition
// EpeeMode.h - Epee-specific configuration and rules



class EpeeMode {
private:
    string HitTypes[6] {"Red_On_Target","Green_On_Target", "Red_Off_Target","Green_Off_Target","Red_Grounding_Hit","Green_Grounding_Hit"};
    int* HitValues[6] = {0, 0, 0, 0, 0, 0}; // Hit values for Red and Green fencers
    Scorebox* scorebox; // Pointer to the Scorebox for managing scores and hits
    GPIO_Manager* gpio; // Pointer to GPIO checker for reading weapon pins
    
    int lockoutTimer = 3000; // The time in milliseconds to lock out after a hit
    bool isLockedOut = false; // Flag to indicate if the scorebox is locked out
    bool lockOutTimerStarted = false; // Flag to indicate if the lockout timer has been started and is running
    unsigned long lockoutStartTime = 0; // Timestamp when the lockout period started

    // Hit state flags
    bool redOnTarget = false;
    bool greenOnTarget = false;

    bool redOffTarget = false;
    bool greenOffTarget = false;

    bool redGrounding = false;
    bool greenGrounding = false;

public:
    EpeeMode(Scorebox* sb);
    void evaluateHit();
    void groundingCheck();
    void onTargetCheck(int* readings);
    void offTargetCheck(int* readings);
    void reset();

};

#endif