//
// Created by ліна on 30.06.2026.
//

#ifndef ASSIGMENT4_CONTACTINFOLINE_H
#define ASSIGMENT4_CONTACTINFOLINE_H
#include "Line.h"

class ContactInfoLine : public Line {
    std::string full_name;
    std::string email;
public:
    ContactInfoLine(const std::string& n, std::string e) : full_name(n), email(e) {}
    void print() const override {
        std::cout << "Full name: " << full_name << ", E-main: " << email << std::endl;
    }
};

#endif //ASSIGMENT4_CONTACTINFOLINE_H
