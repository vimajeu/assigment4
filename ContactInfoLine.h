//
// Created by ліна on 30.06.2026.
//

#ifndef ASSIGMENT4_CONTACTINFOLINE_H
#define ASSIGMENT4_CONTACTINFOLINE_H
#include "Line.h"
#include <iostream>
#include <vector>
#include <string>

class ContactInfoLine : public Line {
    std::string name;
    std::string surname;
    std::string email;
public:
    ContactInfoLine(const std::string& n, const std::string& s, const std::string& e) : name(n), surname(s), email(e) {}
    ContactInfoLine() = default;
    void print() const override {
        std::cout << "Full name: " << name << " " << surname << ", E-mail: " << email << std::endl;
    }
    void serialize(std::vector<uint8_t>& out) const override;
    Line* clone() const override;
    LineType getType() const override;
    static ContactInfoLine* deserialize(const std::vector<uint8_t>& in, size_t& offset);
};

#endif //ASSIGMENT4_CONTACTINFOLINE_H
