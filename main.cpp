// main.cpp - Main program loop
#include "Scorebox.h"
#include "EpeeMode.h"
#include <thread>
#include <chrono>

int main() {
    cout << "=== Fencing Scorebox System ===" << endl;
    cout << "Epee Mode Initialized" << endl;
    
    // Create scorebox and epee mode
    Scorebox scorebox;
    EpeeMode epeeMode(&scorebox);
    
    // Initialize hardware
    scorebox.initialize();
    
    // Start a bout
    epeeMode.startBout();
    
    // Main loop (similar to Arduino loop())
    while (true) {
        // Update scorebox state
        scorebox.update();
        
        // Check win conditions
        if (epeeMode.checkWinCondition()) {
            // Bout ended, wait for reset or new bout
            this_thread::sleep_for(chrono::seconds(5));
            epeeMode.startBout(); // Auto-restart for demo
        }
        
        // Small delay to prevent overwhelming the CPU
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    
    return 0;
}

