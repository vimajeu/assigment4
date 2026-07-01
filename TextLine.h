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
    TextLine() = default;
    void append(std::string& app_text);
    void find_string(std::string& looking_for) const;
    void insert_at(std::string& str, int position);
    void replace_text(std::string& str, int position);
    void delete_text(int position, int amount_of_symbols);
    std::string copy_fragment(int position, int count) const;
    std::string cut_fragment(int position, int count);

    int get_length() const override;
    void print() const override {
        std::cout << "Text: " << text << std::endl;
    }
    void serialize(std::vector<uint8_t>& out) const override;
    Line* clone() const override;
    LineType getType() const override;
    static TextLine* deserialize(const std::vector<uint8_t>& in, size_t& offset);
};

#endif //ASSIGMENT4_TEXTLINE_H
