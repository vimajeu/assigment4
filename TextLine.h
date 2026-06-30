//
// Created by ліна on 30.06.2026.
//

#ifndef ASSIGMENT4_TEXTLINE_H
#define ASSIGMENT4_TEXTLINE_H
#include "Line.h"
#include <iostream>
#include <vector>
#include <string>

class TextLine : public Line {
    std::string text;
public:
    TextLine(const std::string& t) : text(t) {}
    void print() const override {
        std::cout << "Text: " << text << std::endl;
    }
};

#endif //ASSIGMENT4_TEXTLINE_H
