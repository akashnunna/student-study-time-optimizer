#ifndef OPTIMIZER_H
#define OPTIMIZER_H

// ============================================================
//  optimizer.h
//  Declares the Optimizer class
//  Contains the 0/1 Knapsack DP logic
// ============================================================

#include <vector>
#include "subject.h"

using namespace std;

class Optimizer {
private:
    vector<Subject> subjects;       // List of all subjects
    int             totalTime;      // Total available study time (hours)
    int             maxMarks;       // Maximum marks achievable (result)
    vector<Subject> selectedSubjects; // Subjects chosen by knapsack

    // Internal DP function
    void runKnapsack();

public:
    // Constructor
    Optimizer(vector<Subject> subjects, int totalTime);

    // Run the optimizer
    void optimize();

    // Display results
    void displayResults() const;

    // Getters (for testing / external use)
    int            getMaxMarks()       const;
    vector<Subject> getSelectedSubjects() const;
};

#endif
