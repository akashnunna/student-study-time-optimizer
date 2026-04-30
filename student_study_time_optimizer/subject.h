#ifndef SUBJECT_H
#define SUBJECT_H

// ============================================================
//  subject.h
//  Defines the Subject class
//  Each subject has a name, time required, and marks weightage
// ============================================================

#include <string>
using namespace std;

class Subject {
private:
    string name;    // Subject name
    int    time;    // Hours required to study
    int    marks;   // Marks weightage (value/benefit)

public:
    // Constructor
    Subject(string name, int time, int marks);

    // Getters
    string getName()  const;
    int    getTime()  const;
    int    getMarks() const;

    // Display subject details
    void display() const;
};

#endif
