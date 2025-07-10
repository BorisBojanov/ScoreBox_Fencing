// Checks the GPIO pins state and updates the scorebox
#ifndef GPIO_Manager_H
#define GPIO_Manager_H

#include <iostream>
#include <chrono> 
#include <thread>
#include <map>
#include <string>
#include <array>
// #include <Arduino.h> // Include Arduino library for pin manipulation

using namespace std;

#define DEBOUNCE_TIME 10   // 10ms debounce for weapon detection
// Pin definitions for ESP32 (adjust as needed)
enum PinType {
    RED_FENCER_PIN_A,
    RED_FENCER_PIN_B,
    RED_FENCER_PIN_C,
    GREEN_FENCER_PIN_A,
    GREEN_FENCER_PIN_B,
    GREEN_FENCER_PIN_C,
    RED_LED_PIN,
    GREEN_LED_PIN,
    BUZZER_PIN,
    RESET_BUTTON_PIN
};

/*
Array to hold pin readings for both fencers
Assuming 3 pins for each weapon and 2 timestamps
[]
*/
static int readings[8]; 


// Timing constants for Epee (in milliseconds)
#define LOCKOUT_TIME 40    // 40ms lockout period after first hit
#define DEBOUNCE_TIME 10   // 10ms debounce for weapon detection

class GPIO_Manager {
    private:
        int pinNumbers[6] = {2,3,4,5,6,7}; // Array to hold pin numbers for red and green weapons
        unsigned long redHitStartTime;
        unsigned long greenHitStartTime;
        unsigned long lockoutStartTime;
    
        // Hardware checking
        bool readWeaponPins(int pinA, int pinB, int pinC);
        bool resetPins();

    public:
        GPIO_Manager();
        void initialize();
        void update(unsigned long currentTimeNow);
        void reset();
        void setPinNumber(PinType pinType, int newPinNumber);
        void setPinValue(PinType pinType, int value);

        //Getters
        int* getFencerPinReadings();
        int getPinNumber(PinType pinType);
        int getPinType(int pinNumber);


};



#endif // GPIO_Manager_H