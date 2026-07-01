//
// Created by ліна on 30.06.2026.
//

#include "ContactInfoLine.h"

LineType ContactInfoLine::getType() const {
    return LineType::ContactInfo;
}

void ContactInfoLine::serialize(std::vector<uint8_t>& out) const {
    out.push_back(static_cast<uint8_t>(getType()));
    uint32_t name_length = static_cast<uint32_t>(name.size());
    for (int i = 0; i < 4; i++) {
        out.push_back(static_cast<uint8_t>(name_length >> (i * 8) & 0xFF));
    }
    for (char c : name) {
        out.push_back(static_cast<uint8_t>(c));
    }

    uint32_t surname_length = static_cast<uint32_t>(surname.size());
    for (int i = 0; i < 4; i++) {
        out.push_back(static_cast<uint8_t>(surname_length >> (i * 8) & 0xFF));
    }
    for (char c : surname) {
        out.push_back(static_cast<uint8_t>(c));
    }

    uint32_t email_length = static_cast<uint32_t>(email.size());
    for (int i = 0; i < 4; i++) {
        out.push_back(static_cast<uint8_t>(email_length >> (i * 8) & 0xFF));
    }
    for (char c : email) {
        out.push_back(static_cast<uint8_t>(c));
    }
}

Line* ContactInfoLine::clone() const {
    return new ContactInfoLine(name, surname, email);
}

ContactInfoLine* ContactInfoLine::deserialize(const std::vector<uint8_t>& in, size_t& offset) {
    uint32_t name_length = 0;
    for (int i = 0; i < 4; i++) {
        name_length |= static_cast<uint32_t>(in[offset + i]) << (i * 8);
    }
    offset += 4;
    std::string n(in.begin() + offset, in.begin() + offset + name_length);
    offset += name_length;

    uint32_t surname_length = 0;
    for (int i = 0; i < 4; i++) {
        surname_length |= static_cast<uint32_t>(in[offset + i]) << (i * 8);
    }
    offset += 4;
    std::string s(in.begin() + offset, in.begin() + offset + surname_length);
    offset += surname_length;

    uint32_t email_length = 0;
    for (int i = 0; i < 4; i++) {
        email_length |= static_cast<uint32_t>(in[offset + i]) << (i * 8);
    }
    offset += 4;
    std::string e(in.begin() + offset, in.begin() + offset + email_length);
    offset += email_length;
    return new ContactInfoLine(n, s, e);
}
