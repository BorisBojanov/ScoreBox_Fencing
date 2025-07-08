// EpeeMode.cpp - Epee mode implementation
#include "EpeeMode.h"


EpeeMode::EpeeMode(Scorebox* sb) : scorebox(sb) {
}

void EpeeMode::evaluateHit() {

}

void EpeeMode::groundingCheck(){
    // First check for grounding, if grounding is occouriong, then trigger the grounding logic which does not lock ou the scorebox
    // if Red A, Red B, and Green C are T then Red fencer is groudning
    // if Green A, Green B, and Red C are T then Green fencer is grounding
     
}
