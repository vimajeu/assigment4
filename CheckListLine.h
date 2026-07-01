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
    ChecklistLine() = default;
    void toggle();
    void print() const override {
        std::cout << "[ " << (checked ? "x" : " ") << " ] " << item << std::endl;
    }
    void serialize(std::vector<uint8_t>& out) const override;
    Line* clone() const override;
    LineType getType() const override;
    static ChecklistLine* deserialize(const std::vector<uint8_t>& in, size_t& offset);
};

#endif //ASSIGMENT4_CHECKLISTLINE_H
