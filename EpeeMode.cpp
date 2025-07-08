// EpeeMode.cpp - Epee mode implementation
#include "EpeeMode.h"



EpeeMode::EpeeMode(Scorebox* sb) : scorebox(sb)  {
}

/*
This is the core logic for evaluating hits in Epee mode.
if fencing is grounding then it does not lock out the scorebox and does not signal a hit
*/
void EpeeMode::evaluateHit() {

}

void EpeeMode::groundingCheck(){
    // First check for grounding, if grounding is occouriong, then trigger the grounding logic which does not lock ou the scorebox
    // if Red A, Red B, and Green C are T then Red fencer is groudning
    // if Green A, Green B, and Red C are T then Green fencer is grounding
    int* readings = gpio->getFencerPinReadings();
    // [RED_WEAPON_PIN_A, RED_WEAPON_PIN_B, RED_WEAPON_PIN_C, redHitStartTime, GREEN_WEAPON_PIN_A, GREEN_WEAPON_PIN_B, GREEN_WEAPON_PIN_C, greenHitStartTime]
    // Check if Red A, Red B, and Green C are all true
    if (readings[0] && readings[1] && readings[6]) {
        cout << "Red fencer is grounding." << endl;
        //TODO Implement grounding logic here

    // Check if Green A, Green B, and Red C are all true
    } else if (readings[4] && readings[5] && readings[2]) {
        cout << "Green fencer is grounding." << endl;
        //TODO Implement grounding logic here

    } else {
        cout << "No grounding detected." << endl;
    }
}
