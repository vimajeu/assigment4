//
// Created by ліна on 30.06.2026.
//

#include "TextLine.h"
#include <iostream>
#include <string>

void TextLine::append(std::string& app_text) {
    text += app_text;
}

void TextLine::find_string(std::string& looking_for) const {
    size_t position = text.find(looking_for);
    while (position != std::string::npos) {
        std::cout << "String found on position: " << position << std::endl;
        position = text.find(looking_for, position + 1);
    }
}

void TextLine::insert_at(std::string& str, int position) {
    text.insert(position, str);
}

void TextLine::delete_text(int position, int amount_of_symbols) {
    if (position < 0 || position >= text.size()) {
        std::cout << "Error: position out of range" << std::endl;
        return;
    }
    text.erase(position, amount_of_symbols);
}

void TextLine::replace_text(std::string& str, int position) {
    delete_text(position, str.size());
    insert_at(str, position);
}

std::string TextLine::copy_fragment(int position, int count) const {
    if (position < 0 || position >= text.size()) {
        std::cout << "Error: position out of range" << std::endl;
        return "";
    }
    std::string copied_text = text.substr(position, count);
    return copied_text;
}

std::string TextLine::cut_fragment(int position, int count) {
    std::string copied_text = copy_fragment(position, count);
    delete_text(position, count);
    return copied_text;
}

LineType TextLine::getType() const {
    return LineType::Text;
}

void TextLine::serialize(std::vector<uint8_t>& out) const {
    out.push_back(static_cast<uint8_t>(getType()));
    uint32_t length = static_cast<uint32_t>(text.size());
    for (int i = 0; i < 4; i++) {
        out.push_back(static_cast<uint8_t>(length >> (i * 8) & 0xFF));
    }

    for (char c : text) {
        out.push_back(static_cast<uint8_t>(c));
    }
}

Line* TextLine::clone() const {
    return new TextLine(text);
}

TextLine* TextLine::deserialize(const std::vector<uint8_t>& in, size_t& offset) {
    uint32_t length = 0;
    for (int i = 0; i < 4; i++) {
        length |= static_cast<uint32_t>(in[offset + i]) << (i * 8);
    }
    offset += 4;

    std::string data(in.begin() + offset, in.begin() + offset + length);
    offset += length;
    return new TextLine(data);
}

int TextLine::get_length() const {
    return text.size();
}
