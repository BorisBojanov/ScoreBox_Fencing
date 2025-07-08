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
    // Initialize pins for ESP32
    // pinMode(RED_WEAPON_PIN, INPUT_PULLUP);
    // pinMode(GREEN_WEAPON_PIN, INPUT_PULLUP);
    // pinMode(RED_LED_PIN, OUTPUT);
    // pinMode(GREEN_LED_PIN, OUTPUT);
    // pinMode(BUZZER_PIN, OUTPUT);
    // pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
    setPinNumber(RED_WEAPON_PIN_A, 2);
    setPinNumber(RED_WEAPON_PIN_B, 3);
    setPinNumber(RED_WEAPON_PIN_C, 4);
    setPinNumber(GREEN_WEAPON_PIN_A, 5);
    setPinNumber(GREEN_WEAPON_PIN_B, 6);
    setPinNumber(GREEN_WEAPON_PIN_C, 7);
    
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

// Get the pin readings for the fencer side (Red or Green).
// also includes time of readings
// Returns an array of pin readings based on the fencer side (Red or Green).
int* GPIO_Checker::getPinReadings(string RedOrGreen) {
    static int readings[4]; // Assuming 3 pins for each weapon
    if (RedOrGreen == "Red") {
        readings[0] = pinNumbers[RED_WEAPON_PIN_A];
        readings[1] = pinNumbers[RED_WEAPON_PIN_B];
        readings[2] = pinNumbers[RED_WEAPON_PIN_C];
        readings[3] = redHitStartTime; // Include the time of the hit
    } else if (RedOrGreen == "Green") {
        readings[0] = pinNumbers[GREEN_WEAPON_PIN_A];
        readings[1] = pinNumbers[GREEN_WEAPON_PIN_B];
        readings[2] = pinNumbers[GREEN_WEAPON_PIN_C];
        readings[3] = greenHitStartTime; // Include the time of the hit
    } else {
        throw std::invalid_argument("Invalid weapon type specified.");
    }
    return readings;
}