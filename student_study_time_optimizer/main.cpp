// ============================================================
//  main.cpp
//  Student Study Time Optimizer
//  Algorithm : 0/1 Knapsack (Dynamic Programming)
// ============================================================

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "subject.h"
#include "optimizer.h"

using namespace std;

// ─── Helper: print a divider line ───────────────────────────
void printLine() {
    cout << "------------------------------------------------------------\n";
}

// ─── Display all subjects in a formatted table ───────────────
void displaySubjectTable(const vector<Subject>& subjects) {
    cout << "\n";
    printLine();
    cout << "  " << left
         << setw(5)  << "No."
         << setw(20) << "Subject"
         << setw(12) << "Time (hrs)"
         << "Marks\n";
    printLine();
    for (int i = 0; i < (int)subjects.size(); i++) {
        cout << "  " << left
             << setw(5)  << (i + 1)
             << setw(20) << subjects[i].getName()
             << setw(12) << subjects[i].getTime()
             << subjects[i].getMarks() << "\n";
    }
    printLine();
    cout << "\n";
}

// ─── Load preset subjects (8 subjects) ──────────────────────
vector<Subject> loadPreset() {
    return {
        Subject("Mathematics",        3, 10),
        Subject("Physics",            4, 12),
        Subject("Chemistry",          2,  7),
        Subject("Computer Science",   5, 15),
        Subject("English",            1,  5),
        Subject("Biology",            3,  9),
        Subject("Economics",          2,  8),
        Subject("History",            1,  4)
    };
}

// ─── Get subjects from user input ───────────────────────────
vector<Subject> getSubjectsFromUser() {
    int n;
    cout << "\n  How many subjects do you want to enter? ";
    cin >> n;
    cin.ignore();

    vector<Subject> subjects;
    cout << "\n  Enter details for each subject:\n";
    printLine();

    for (int i = 0; i < n; i++) {
        string name;
        int    time, marks;

        cout << "\n  Subject " << (i + 1) << ":\n";
        cout << "    Name        : ";
        getline(cin, name);
        cout << "    Time (hrs)  : ";
        cin >> time;
        cout << "    Marks       : ";
        cin >> marks;
        cin.ignore();

        subjects.push_back(Subject(name, time, marks));
    }
    return subjects;
}

// ─── Show the DP table (for understanding) ──────────────────
void showDPTable(const vector<Subject>& subjects, int totalTime) {
    int n = subjects.size();

    // Rebuild DP table
    vector<vector<int>> dp(n + 1, vector<int>(totalTime + 1, 0));
    for (int i = 1; i <= n; i++) {
        int st = subjects[i-1].getTime();
        int sm = subjects[i-1].getMarks();
        for (int t = 0; t <= totalTime; t++) {
            dp[i][t] = dp[i-1][t];
            if (st <= t && dp[i-1][t-st] + sm > dp[i][t])
                dp[i][t] = dp[i-1][t-st] + sm;
        }
    }

    cout << "\n  DP Table (rows=subjects, cols=time 0.." << totalTime << "):\n\n";
    cout << "        ";
    for (int t = 0; t <= totalTime; t++)
        cout << setw(4) << t;
    cout << "\n  ";
    printLine();

    for (int i = 0; i <= n; i++) {
        if (i == 0)
            cout << "  " << setw(6) << "Base" << "  ";
        else
            cout << "  " << setw(6) << subjects[i-1].getName().substr(0,6) << "  ";
        for (int t = 0; t <= totalTime; t++)
            cout << setw(4) << dp[i][t];
        cout << "\n";
    }
    cout << "\n";
}

// ─── Main Menu ───────────────────────────────────────────────
int main() {
    cout << "\n";
    cout << "============================================================\n";
    cout << "       STUDENT STUDY TIME OPTIMIZER                        \n";
    cout << "       Algorithm: 0/1 Knapsack (Dynamic Programming)       \n";
    cout << "============================================================\n";

    // --- Choose mode ---
    int mode = 0;
    cout << "\n  Select mode:\n";
    cout << "    [1] Use preset subjects (8 subjects - recommended)\n";
    cout << "    [2] Enter your own subjects\n";
    cout << "\n  Choice: ";
    cin >> mode;
    cin.ignore();

    vector<Subject> subjects;

    if (mode == 1) {
        subjects = loadPreset();
        cout << "\n  Preset subjects loaded.\n";
    } else {
        subjects = getSubjectsFromUser();
    }

    // --- Display subject table ---
    cout << "\n  All Subjects:\n";
    displaySubjectTable(subjects);

    // --- Get total study time ---
    int totalTime = 0;
    cout << "  Enter total available study time (in hours): ";
    cin >> totalTime;

    if (totalTime <= 0) {
        cout << "\n  [!] Invalid time. Please enter a positive number.\n\n";
        return 1;
    }

    // --- Optional: Show DP table ---
    char showTable;
    cout << "\n  Show DP table step-by-step? (y/n): ";
    cin >> showTable;

    if (showTable == 'y' || showTable == 'Y') {
        showDPTable(subjects, totalTime);
    }

    // --- Run optimizer ---
    Optimizer optimizer(subjects, totalTime);
    optimizer.optimize();

    // --- Display results ---
    optimizer.displayResults();

    return 0;
}
