//
// Created by ліна on 30.06.2026.
//

#ifndef ASSIGMENT4_TEXTEDITOR_H
#define ASSIGMENT4_TEXTEDITOR_H
#include <iostream>
#include <vector>
#include <string>

#include "Line.h"

class TextEditor {
    std::vector<Line*> lines;
public:
    void addLine(Line* line) {
        lines.push_back(line);
    }
    void printAll() const {
        for (size_t i = 0; i < lines.size(); ++i) {
            lines[i]->print();
        }
    }
    ~TextEditor() {
        for (size_t i = 0; i < lines.size(); ++i) {
            delete lines[i];
        }
    }
};

#endif //ASSIGMENT4_TEXTEDITOR_H
