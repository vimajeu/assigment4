//
// Created by ліна on 30.06.2026.
//

#ifndef ASSIGMENT4_TEXTEDITOR_H
#define ASSIGMENT4_TEXTEDITOR_H
#include <iostream>
#include <vector>
#include <string>

#include "Line.h"
#include "Text.h"

class TextEditor {
    Text text;
    void show_menu();
    void handle_command(int choice);
public:
    void run();
};

#endif //ASSIGMENT4_TEXTEDITOR_H
