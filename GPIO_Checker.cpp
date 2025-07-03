/*
This class is meant for the score box to be able to all one very simple function when an ISR is triggered by a GPIO pin.
It checks the GPIO pins state and updates the scorebox. 

Change the GPIO pin numbers to match your hardware setup.

*/
#include "GPIO_Checker.h"
GPIO_Checker::GPIO_Checker() : locked(false), redHit(false), greenHit(false), redHitStartTime(0), greenHitStartTime(0), lockoutStartTime(0) {
}

bool GPIO_Checker::readWeaponPins(int pinA, int pinB, int pinC){
    return false;
}

bool GPIO_Checker::resetPins(){
    return false;
}

void GPIO_Checker::initialize(){
    // Initialize GPIO pins, set modes, etc.
    cout << "GPIO Checker initialized." << endl;
}

/*
Used to update the state of the GPIO pins and check for hits.

Parameters:
- currentTime: The current time in milliseconds since epoch, used for timing checks.
    unsigned long currentTimeNow = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();

*/
void GPIO_Checker::update(unsigned long currentTimeNow) {
    // Update the state of the GPIO pins
    // unsigned long currentTimeNow = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
    if (locked)  {
        if (currentTimeNow > lockoutStartTime + LOCKOUT_TIME) {
            locked = false; // Lockout period ended
            redHit = false;
            greenHit = false;
            cout << "Lockout period ended." << endl;
        }
    }
    else {
        // Check for hits
        if (readWeaponPins(RED_WEAPON_PIN_A, RED_WEAPON_PIN_B, RED_WEAPON_PIN_C)) {
            redHit = true;
            redHitStartTime = currentTimeNow;
            lockoutStartTime = currentTimeNow;
            locked = true;
            cout << "Red hit detected!" << endl;
        }
        else if (readWeaponPins(GREEN_WEAPON_PIN_A, GREEN_WEAPON_PIN_B, GREEN_WEAPON_PIN_C)) {
            greenHit = true;
            greenHitStartTime = currentTimeNow;
            lockoutStartTime = currentTimeNow;
            locked = true;
            cout << "Green hit detected!" << endl;
        }
    }
}

void GPIO_Checker::reset() {
    locked = false;
    redHit = false;
    greenHit = false;
    redHitStartTime = 0;
    greenHitStartTime = 0;
    lockoutStartTime = 0;
    cout << "GPIO Checker reset." << endl;
}

void GPIO_Checker::setPinNumber(PinType pinType, int newPinNumber){
    pinNumbers[pinType] = newPinNumber;
}

int GPIO_Checker::getPinNumber(PinType pinType){
    return pinNumbers[pinType];
}

int GPIO_Checker::getPinType(int pinNumber){
    for (int i = 0; i < 6; i++) {
        if (pinNumbers[i] == pinNumber) {
            return static_cast<PinType>(i); // Return the index as the PinType
        }
    }
    // if not found, throw an exception
    throw std::invalid_argument("Pin number not found in pinNumbers array.");
}
