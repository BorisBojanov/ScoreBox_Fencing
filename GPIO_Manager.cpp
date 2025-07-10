/*
This class is meant for the score box to be able to all one very simple function when an ISR is triggered by a GPIO pin.
It checks the GPIO pins state and updates the scorebox. 

Change the GPIO pin numbers to match your hardware setup.

*/
#include "GPIO_Manager.h"
GPIO_Manager::GPIO_Manager() : redHitStartTime(0), greenHitStartTime(0), lockoutStartTime(0) {
    initialize();
}

bool GPIO_Manager::readWeaponPins(int pinA, int pinB, int pinC){
    return false;
}

bool GPIO_Manager::resetPins(){
    return false;
}

void GPIO_Manager::initialize(){
    // Initialize GPIO pins, set modes, etc.
    // Initialize pins for ESP32
    // pinMode(RED_WEAPON_PIN, INPUT_PULLUP);
    // pinMode(GREEN_WEAPON_PIN, INPUT_PULLUP);
    // pinMode(RED_LED_PIN, OUTPUT);
    // pinMode(GREEN_LED_PIN, OUTPUT);
    // pinMode(BUZZER_PIN, OUTPUT);
    // pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
    setPinNumber(RED_FENCER_PIN_A, 2);
    setPinNumber(RED_FENCER_PIN_B, 3);
    setPinNumber(RED_FENCER_PIN_C, 4);
    setPinNumber(GREEN_FENCER_PIN_A, 5);
    setPinNumber(GREEN_FENCER_PIN_B, 6);
    setPinNumber(GREEN_FENCER_PIN_C, 7);
    setPinNumber(RED_LED_PIN, 8);
    setPinNumber(GREEN_LED_PIN, 9);
    setPinNumber(BUZZER_PIN, 10);
    setPinNumber(RESET_BUTTON_PIN, 11);

    
    cout << "GPIO Checker initialized." << endl;
}

/*
Used to update the state of the GPIO pins and check for hits.
this function should be called by an ISR (Interrupt Service Routine) 

Parameters:
- currentTime: The current time in milliseconds since epoch, used for timing checks.
    unsigned long currentTimeNow = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
*/
void GPIO_Manager::update(unsigned long currentTimeNow) {
    // Update the state of the GPIO pins
    // unsigned long currentTimeNow = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();
    
}

/*
Get the pin readings for the both fencers).
also includes time of readings
Returns an array of pin readings index 0-3 contains red weapon readings, index 4-7 contains green weapon readings
*/
int* GPIO_Manager::getFencerPinReadings() {
    // readings arrray defined in the header file
        readings[0] = pinNumbers[RED_FENCER_PIN_A];
        readings[1] = pinNumbers[RED_FENCER_PIN_B];
        readings[2] = pinNumbers[RED_FENCER_PIN_C];
        readings[3] = redHitStartTime; // Include the time of the hit
        readings[4] = pinNumbers[GREEN_FENCER_PIN_A];
        readings[5] = pinNumbers[GREEN_FENCER_PIN_B];
        readings[6] = pinNumbers[GREEN_FENCER_PIN_C];
        readings[7] = greenHitStartTime; // Include the time of the hit
    return readings;
}

void GPIO_Manager::setPinNumber(PinType pinType, int newPinNumber){
    pinNumbers[pinType] = newPinNumber;
}

/*
Usaed to set the value of LEDs, buzzer, reset button, or any other pin that is not a weapon pin.
*/
void GPIO_Manager::setPinValue(PinType pinType, int value){
    // Set the pin value for LEDs, buzzer, or reset button
    // if using Arduino:
    // digitalWrite(pinNumbers[pinType], value);
    cout << "Setting pin " << pinNumbers[pinType] << " to value " << value << endl;
}

int GPIO_Manager::getPinNumber(PinType pinType){
    return pinNumbers[pinType];
}

int GPIO_Manager::getPinType(int pinNumber){
    for (int i = 0; i < 6; i++) {
        if (pinNumbers[i] == pinNumber) {
            return static_cast<PinType>(i); // Return the index as the PinType
        }
    }
    // if not found, throw an exception
    throw std::invalid_argument("Pin number not found in pinNumbers array.");
}
