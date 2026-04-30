// ============================================================
//  optimizer.cpp
//  Implements the 0/1 Knapsack Dynamic Programming algorithm
//
//  Core Idea:
//  - Each subject is either fully studied (1) or skipped (0)
//  - Build a 2D DP table where:
//      dp[i][t] = max marks using first i subjects
//                 within t hours of study time
//  - Trace back the table to find which subjects were selected
// ============================================================

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "optimizer.h"

using namespace std;

// ─── Constructor ────────────────────────────────────────────
Optimizer::Optimizer(vector<Subject> subjects, int totalTime)
    : subjects(subjects), totalTime(totalTime), maxMarks(0) {}

// ─── runKnapsack (Private) ──────────────────────────────────
//  Builds the DP table and traces back selected subjects
void Optimizer::runKnapsack() {
    int n = subjects.size();

    // Step 1: Create DP table of size (n+1) x (totalTime+1)
    //         Initialized to 0
    //
    //         dp[i][t] = best marks using subjects 0..i-1
    //                    with t hours available
    //
    vector<vector<int>> dp(n + 1, vector<int>(totalTime + 1, 0));

    // Step 2: Fill the DP table
    for (int i = 1; i <= n; i++) {
        int subjectTime  = subjects[i - 1].getTime();
        int subjectMarks = subjects[i - 1].getMarks();

        for (int t = 0; t <= totalTime; t++) {
            // Option A: Skip subject i — carry forward previous result
            dp[i][t] = dp[i - 1][t];

            // Option B: Include subject i — only if time allows
            if (subjectTime <= t) {
                int marksIfIncluded = dp[i - 1][t - subjectTime] + subjectMarks;

                // Take the better option
                if (marksIfIncluded > dp[i][t]) {
                    dp[i][t] = marksIfIncluded;
                }
            }
        }
    }

    // Step 3: Maximum marks is at dp[n][totalTime]
    maxMarks = dp[n][totalTime];

    // Step 4: Traceback — find which subjects were selected
    //         Start from bottom-right of table
    //         If dp[i][t] != dp[i-1][t], subject i was included
    selectedSubjects.clear();
    int t = totalTime;
    for (int i = n; i >= 1; i--) {
        if (dp[i][t] != dp[i - 1][t]) {
            // Subject i was included
            selectedSubjects.push_back(subjects[i - 1]);
            t -= subjects[i - 1].getTime(); // Reduce available time
        }
    }

    // Reverse to show in original order
    reverse(selectedSubjects.begin(), selectedSubjects.end());
}

// ─── optimize (Public) ──────────────────────────────────────
void Optimizer::optimize() {
    runKnapsack();
}

// ─── displayResults ─────────────────────────────────────────
void Optimizer::displayResults() const {

    cout << "\n";
    cout << "============================================================\n";
    cout << "               STUDY TIME OPTIMIZER - RESULTS              \n";
    cout << "============================================================\n";

    cout << "\n  Total Study Time Available : " << totalTime << " hours\n";
    cout << "  Total Subjects Considered  : " << subjects.size() << "\n";

    cout << "\n------------------------------------------------------------\n";
    cout << "  Maximum Marks Achievable   : " << maxMarks << "\n";
    cout << "------------------------------------------------------------\n";

    cout << "\n  Selected Subjects (" << selectedSubjects.size() << "):\n\n";

    int totalTimeUsed  = 0;
    int totalMarksSum  = 0;

    for (const Subject& s : selectedSubjects) {
        s.display();
        totalTimeUsed += s.getTime();
        totalMarksSum += s.getMarks();
    }

    cout << "\n------------------------------------------------------------\n";
    cout << "  Total Time Used  : " << totalTimeUsed << " / "
         << totalTime << " hours\n";
    cout << "  Total Marks      : " << totalMarksSum << "\n";
    cout << "============================================================\n\n";
}

// ─── Getters ────────────────────────────────────────────────
int Optimizer::getMaxMarks() const {
    return maxMarks;
}

vector<Subject> Optimizer::getSelectedSubjects() const {
    return selectedSubjects;
}
