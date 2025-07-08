// Scorebox header file
#ifndef SCOREBOX_H
#define SCOREBOX_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
// #include <Arduino>
#include <GPIO_Checker.h> // Hardware interface for GPIO pins
#include <Display.h> // Display interface for showing scores
#include <Match.h> // Match management for Epee mode
GPIO_Checker gpioChecker;
Display display;
Match match;

// Pin definitions for ESP32 (adjuwst as needed)
#define RED_LED_PIN 18
#define GREEN_LED_PIN 19
#define BUZZER_PIN 21
#define RESET_BUTTON_PIN 22

// Timing constants for Epee (in milliseconds)
#define LOCKOUT_TIME 40    // 40ms lockout period after first hit
#define DISPLAY_TIME 3000  // 3 seconds to display hits

using namespace std;

class Scorebox {
private:
    bool isLocked;
    bool redHit;
    bool greenHit;
    unsigned long hitStartTime;
    unsigned long lockoutStartTime;
    int redScore;
    int greenScore;
    
    // Hardware interface methods
    // bool readWeaponPin(int pin);
    void setLED(int pin, bool state);
    void setBuzzer(bool state);
    bool readResetButton();
    
public:
    Scorebox();
    void initialize();
    void update();
    void reset();
    void displayScores();
    
    // Getters
    int getRedScore() const { return redScore; }
    int getGreenScore() const { return greenScore; }
};

#endif