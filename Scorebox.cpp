// Score box class implementation


#include "Scorebox.h"

// Constructor initializes the scorebox state
Scorebox::Scorebox() : isLocked(false), redHit(false), greenHit(false), 
                       hitStartTime(0), lockoutStartTime(0), redScore(0), greenScore(0) {
    
}

void Scorebox::initialize() {
    // Initialize stuff
    // gpioChecker.initialize();
    // display.initialize();
    // match.initialize();
    
    cout << "Scorebox initialized for Epee mode" << endl;
    reset();
}

void Scorebox::update() {
    // Centrilized method for updating the scorebox state 
    unsigned long currentTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
}

void Scorebox::reset() {
    isLocked = false;
    redHit = false;
    greenHit = false;
    hitStartTime = 0;
    lockoutStartTime = 0;
    
    // Turn off all indicators
    setLED(RED_LED_PIN, false);
    setLED(GREEN_LED_PIN, false);
    setBuzzer(false);
    
    cout << "Scorebox reset - Ready for next action" << endl;
}

void Scorebox::displayScores() {
    cout << "Current Scores - Red: " << redScore << " | Green: " << greenScore << endl;
}

void Scorebox::setLED(int pin, bool state) {
    // Mock implementation - replace with actual ESP32 digitalWrite
    // digitalWrite(pin, state ? HIGH : LOW);
    
    string ledName = (pin == RED_LED_PIN) ? "RED" : "GREEN";
    cout << ledName << " LED: " << (state ? "ON" : "OFF") << endl;
}

void Scorebox::setBuzzer(bool state) {
    // Mock implementation - replace with actual ESP32 digitalWrite
    // digitalWrite(BUZZER_PIN, state ? HIGH : LOW);
    
    cout << "Buzzer: " << (state ? "ON" : "OFF") << endl;
}

bool Scorebox::readResetButton() {
    // Mock implementation - replace with actual ESP32 digitalRead
    // return digitalRead(RESET_BUTTON_PIN) == LOW;
    
    return false; // For testing
}
