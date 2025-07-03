// Score box class implementation


#include "Scorebox.h"

Scorebox::Scorebox() : isLocked(false), redHit(false), greenHit(false), 
                       hitStartTime(0), lockoutStartTime(0), redScore(0), greenScore(0) {
}

void Scorebox::initialize() {
    // Initialize pins for ESP32
    // pinMode(RED_WEAPON_PIN, INPUT_PULLUP);
    // pinMode(GREEN_WEAPON_PIN, INPUT_PULLUP);
    // pinMode(RED_LED_PIN, OUTPUT);
    // pinMode(GREEN_LED_PIN, OUTPUT);
    // pinMode(BUZZER_PIN, OUTPUT);
    // pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
    
    cout << "Scorebox initialized for Epee mode" << endl;
    reset();
}

void Scorebox::update() {
    unsigned long currentTime = chrono::duration_cast<chrono::milliseconds>(
        chrono::steady_clock::now().time_since_epoch()).count();
    
    //TODO I want to do this check else where
    // // If we're displaying a hit, check if display time is over
    // if (isHitRegistered() && (currentTime - hitStartTime > DISPLAY_TIME)) {
    //     // Turn off LEDs and buzzer
    //     setLED(RED_LED_PIN, false);
    //     setLED(GREEN_LED_PIN, false);
    //     setBuzzer(false);
    //     redHit = false;
    //     greenHit = false;
    //     isLocked = false;
    //     return;
    // }
    
    // If we're in lockout period, check for second hit
    if (isLocked && (!greenHit || !redHit)) {
        if (currentTime - lockoutStartTime > LOCKOUT_TIME) {
            isLocked = false; // Lockout period ended
            return;
        }
        
        // Check for second hit during lockout
        if (!redHit && readWeaponPin(RED_WEAPON_PIN)) {
            redHit = true;
            redScore++;
            setLED(RED_LED_PIN, true);
            setBuzzer(true);
            hitStartTime = currentTime;
            cout << "Red hit during lockout! Score: " << redScore << endl;
        }
        
        if (!greenHit && readWeaponPin(GREEN_WEAPON_PIN)) {
            greenHit = true;
            greenScore++;
            setLED(GREEN_LED_PIN, true);
            setBuzzer(true);
            hitStartTime = currentTime;
            cout << "Green hit during lockout! Score: " << greenScore << endl;
        }
        
        return;
    }
    
    // Normal operation - check for first hit
    if (!isLocked && !isHitRegistered()) {
        if (readWeaponPin(RED_WEAPON_PIN)) {
            redHit = true;
            redScore++;
            setLED(RED_LED_PIN, true);
            setBuzzer(true);
            hitStartTime = currentTime;
            lockoutStartTime = currentTime;
            isLocked = true;
            cout << "Red hit! Starting lockout. Score: " << redScore << endl;
        }
        else if (readWeaponPin(GREEN_WEAPON_PIN)) {
            greenHit = true;
            greenScore++;
            setLED(GREEN_LED_PIN, true);
            setBuzzer(true);
            hitStartTime = currentTime;
            lockoutStartTime = currentTime;
            isLocked = true;
            cout << "Green hit! Starting lockout. Score: " << greenScore << endl;
        }
    }
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

// Hardware interface methods (mock implementations for testing)
bool Scorebox::readWeaponPin(int pin) {
    // Mock implementation - replace with actual ESP32 digitalRead
    // return digitalRead(pin) == LOW; // Assuming active low
    
    // For testing purposes, return false
    return false;
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