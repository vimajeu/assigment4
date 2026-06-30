//
// Created by ліна on 30.06.2026.
//

#ifndef ASSIGMENT4_CHECKLISTLINE_H
#define ASSIGMENT4_CHECKLISTLINE_H
#include <iostream>
#include <vector>
#include <string>
#include "Line.h"

class ChecklistLine : public Line {
    std::string item;
    bool checked;
public:
    ChecklistLine(const std::string& i, bool c) : item(i), checked(c) {}
    void print() const override {
        std::cout << "[ " << (checked ? "x" : " ") << " ] " << item << std::endl;
    }
};

#endif //ASSIGMENT4_CHECKLISTLINE_H
