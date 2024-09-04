#include <bits/stdc++.h>
using namespace std;

// Global variable to store the initial strength of Abhimanyu
int initialStrength;

// Memoization function to check if Abhimanyu can pass through the Chakravyuha
bool canPassChakravyuha(int level, int &totalLevels, vector<int> foes, int currentStrength, 
                        int skipsRemaining, int rechargesAvailable, 
                        vector<vector<vector<vector<int>>>> &memo) {
    
    // If Abhimanyu has crossed all levels
    if (level == totalLevels) {
        return (currentStrength >= 0);
    }

    // If the state has been computed, return the saved result
    if (memo[level][currentStrength][skipsRemaining][rechargesAvailable] != -1)
        return memo[level][currentStrength][skipsRemaining][rechargesAvailable];

    bool canAdvance = false;

    // If Abhimanyu has enough strength to overcome the foe at the current level
    if (currentStrength >= foes[level]) {
        canAdvance |= canPassChakravyuha(level + 1, totalLevels, foes, currentStrength - foes[level], 
                                          skipsRemaining, rechargesAvailable, memo);
    }

    // Special case for foes with regenerative power
    if (level == 2 || level == 6) {
        foes[level + 1] += foes[level] / 2;
    }

    // If Abhimanyu can skip this level
    if (skipsRemaining > 0) {
        canAdvance |= canPassChakravyuha(level + 1, totalLevels, foes, currentStrength, 
                                          skipsRemaining - 1, rechargesAvailable, memo);
    }

    // If Abhimanyu can recharge his strength
    if (rechargesAvailable > 0) {
        currentStrength = initialStrength;
        canAdvance |= canPassChakravyuha(level + 1, totalLevels, foes, currentStrength, 
                                          skipsRemaining, rechargesAvailable - 1, memo);
    }

    // Store and return the result for the current state
    return memo[level][currentStrength][skipsRemaining][rechargesAvailable] = canAdvance;
}

// Function to handle each test case
void processTestCase() {
    int totalLevels = 11, strength, skipChances, rechargeChances;
    
    // Read input values: strength, skip chances, recharge chances
    cin >> strength >> skipChances >> rechargeChances;
    initialStrength = strength;
    
    vector<int> foes(totalLevels, 0);
    // Read input values for each foe's strength in the 11 levels
    for (int i = 0; i < totalLevels; i++) {
        cin >> foes[i];
    }

    // Memoization table to store results of subproblems
    vector<vector<vector<vector<int>>>> memo(12, vector<vector<vector<int>>>(205, vector<vector<int>>(20, vector<int>(20, -1))));

    // Check if Abhimanyu can pass through the Chakravyuha
    bool isAbhimanyuVictorious = canPassChakravyuha(0, totalLevels, foes, strength, skipChances, rechargeChances, memo);
    
    if (isAbhimanyuVictorious) {
        cout << "Abhimanyu can pass the Chakravyuha: WIN" << endl;
    } else {
        cout << "Abhimanyu cannot pass the Chakravyuha: LOST" << endl;
    }
}

// Main function
int main() {
    int testCount;
    // Read number of test cases
    cin >> testCount;
    while (testCount--) {
        processTestCase();
    }
    return 0;
}
