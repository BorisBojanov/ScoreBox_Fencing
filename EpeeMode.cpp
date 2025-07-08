// EpeeMode.cpp - Epee mode implementation
#include "EpeeMode.h"



EpeeMode::EpeeMode(Scorebox* sb) : scorebox(sb)  {
}

/*
This is the core logic for evaluating hits in Epee mode.
Check for grounding
    True: if fencers is grounding then it does not lock out the scorebox and does not signal a hit
    Flase: if the fencers are not grounding, then check if the hit is on target, or off target, in epee mode there is no off target hit. 

check if the 'isLockedOut' is Ture or False,
    True: Then ignore the hit and return
    False: Then check if the hit is On_Target or Off_Target
        Off_Target: if true, then signal the hit to the scorebox and set the 'locked_out' state to True
            Check if the lock out timer has previously been started
                TRUE: IF lock out timer has been started, then return off target hit
                False If lock out timer has not been started, then start the lock out timer and return off target hit

        On_Target: if true, then check if the lock out timer is active
            Check if the lock out timer has previously been started
                True: if lock out timer has been started, then return on target hit
                False: if lock out timer has not been started, then start the lock out timer and return on target hit

*/
void EpeeMode::evaluateHit() {
    groundingCheck(); // Check for grounding first
}

/*
First check for grounding, if grounding is occouriong, then trigger the grounding logic which does not lock ou the scorebox
if Red A, Red B, and Green C are T then Red fencer is groudning
if Green A, Green B, and Red C are T then Green fencer is grounding

return to the main logic of the evaluateHit function
*/
void EpeeMode::groundingCheck(){

    int* readings = gpio->getFencerPinReadings();
    // [RED_WEAPON_PIN_A, RED_WEAPON_PIN_B, RED_WEAPON_PIN_C, redHitStartTime, GREEN_WEAPON_PIN_A, GREEN_WEAPON_PIN_B, GREEN_WEAPON_PIN_C, greenHitStartTime]
    // Check if Red A, Red B, and Green C are all true
    if (readings[0] && readings[1] && readings[6]) {
        cout << "Red fencer is grounding." << endl;
        redGrounding = true;
        //TODO Implement grounding logic here

    // Check if Green A, Green B, and Red C are all true
    } else if (readings[4] && readings[5] && readings[2]) {
        cout << "Green fencer is grounding." << endl;
        greenGrounding = true;
        //TODO Implement grounding logic here

    } else {
        cout << "No grounding detected." << endl;
    }
}
