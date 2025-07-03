// Checks the GPIO pins state and updates the scorebox
#ifndef GPIO_CHECKER_H
#define GPIO_CHECKER_H

#include <iostream>
#include <chrono> 
#include <thread>
#include <map>
#include <string>

using namespace std;

enum PinType {
    RED_WEAPON_PIN_A,
    RED_WEAPON_PIN_B,
    RED_WEAPON_PIN_C,
    GREEN_WEAPON_PIN_A,
    GREEN_WEAPON_PIN_B,
    GREEN_WEAPON_PIN_C
};

// Timing constants for Epee (in milliseconds)
#define LOCKOUT_TIME 40    // 40ms lockout period after first hit
#define DEBOUNCE_TIME 10   // 10ms debounce for weapon detection

class GPIO_Checker {
    private:
        int pinNumbers[6] = {2,3,4,5,6,7}; // Array to hold pin numbers for red and green weapons
        bool locked;
        bool redHit;
        bool greenHit;
        unsigned long redHitStartTime;
        unsigned long greenHitStartTime;
        unsigned long lockoutStartTime;
    
        // Hardware checking
        bool readWeaponPins(int pinA, int pinB, int pinC);
        bool resetPins();

    public:
        GPIO_Checker();
        void initialize();
        void update(unsigned long currentTimeNow);
        void reset();
        void setPinNumber(PinType pinType, int newPinNumber);


        //Getters
        bool isLocked() const { return locked; }
        bool hitRegistered() const { return redHit || greenHit; }
        int getPinNumber(PinType pinType);
        int getPinType(int pinNumber);
};



#endif // GPIO_CHECKER_H