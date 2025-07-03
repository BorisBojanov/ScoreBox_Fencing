// EpeeMode.cpp - Epee mode implementation
#include "EpeeMode.h"


EpeeMode::EpeeMode(Scorebox* sb) : scorebox(sb), targetScore(15), maxTime(540), // 9 minutes
                                   boutStartTime(0), boutActive(false) {
}

void EpeeMode::startBout() {
    boutStartTime = chrono::duration_cast<chrono::seconds>(
        chrono::steady_clock::now().time_since_epoch()).count();
    boutActive = true;
    scorebox->reset();
    cout << "Epee bout started! First to " << targetScore << " points wins." << endl;
    cout << "Maximum time: " << maxTime / 60 << " minutes" << endl;
}

void EpeeMode::endBout() {
    boutActive = false;
    cout << "Bout ended!" << endl;
    displayBoutStatus();
}

bool EpeeMode::checkWinCondition() {
    if (!boutActive) return false;
    
    // Check score-based win condition
    if (scorebox->getRedScore() >= targetScore) {
        cout << "Red fencer wins by score!" << endl;
        endBout();
        return true;
    }
    
    if (scorebox->getGreenScore() >= targetScore) {
        cout << "Green fencer wins by score!" << endl;
        endBout();
        return true;
    }
    
    // Check time-based end condition
    if (getTimeRemaining() <= 0) {
        cout << "Time expired!" << endl;
        if (scorebox->getRedScore() > scorebox->getGreenScore()) {
            cout << "Red fencer wins by score!" << endl;
        } else if (scorebox->getGreenScore() > scorebox->getRedScore()) {
            cout << "Green fencer wins by score!" << endl;
        } else {
            cout << "Bout ends in a tie!" << endl;
        }
        endBout();
        return true;
    }
    
    return false;
}

void EpeeMode::displayBoutStatus() {
    scorebox->displayScores();
    if (boutActive) {
        cout << "Time remaining: " << getTimeRemaining() << " seconds" << endl;
    }
}

int EpeeMode::getTimeRemaining() {
    if (!boutActive) return 0;
    
    unsigned long currentTime = chrono::duration_cast<chrono::seconds>(
        chrono::steady_clock::now().time_since_epoch()).count();
    
    int elapsed = currentTime - boutStartTime;
    return max(0, maxTime - elapsed);
}

void EpeeMode::resetScores() {
    scorebox->reset();
    cout << "Scores reset to 0-0" << endl;
}

