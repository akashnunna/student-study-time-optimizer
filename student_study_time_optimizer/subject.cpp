// ============================================================
//  subject.cpp
//  Implements Subject class methods
// ============================================================

#include <iostream>
#include <iomanip>
#include "subject.h"

using namespace std;

// ─── Constructor ────────────────────────────────────────────
Subject::Subject(string name, int time, int marks)
    : name(name), time(time), marks(marks) {}

// ─── Getters ────────────────────────────────────────────────
string Subject::getName()  const { return name;  }
int    Subject::getTime()  const { return time;  }
int    Subject::getMarks() const { return marks; }

// ─── Display ────────────────────────────────────────────────
void Subject::display() const {
    cout << "  " << left << setw(20) << name
         << "Time = " << setw(3) << time  << " hrs   "
         << "Marks = " << marks << "\n";
}
