//
// Created by ліна on 30.06.2026.
//
#ifndef ASSIGMENT4_LINE_H
#define ASSIGMENT4_LINE_H
#include <iostream>
#include <vector>
#include <string>

enum class LineType {
    Text,
    ContactInfo,
    CheckList
};
class Line {
public:
    virtual void print() const = 0;
    virtual void serialize(std::vector<uint8_t>& out) const = 0;
    virtual Line* clone() const = 0;
    virtual LineType getType() const = 0;
    virtual int get_length() const = 0;
    virtual ~Line();
};

#endif //ASSIGMENT4_LINE_H
