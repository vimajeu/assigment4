//
// Created by ліна on 01.07.2026.
//

#ifndef ASSIGMENT4_TEXT_H
#define ASSIGMENT4_TEXT_H
#include <string>
#include "Line.h"
#include <vector>

class Text {
    std::vector<Line*> lines;
    std::string text_buffer = "";
    Line* line_buffer = nullptr;
    // std::vector<Command*> undoStack;
    // std::vector<Command*> redoStack;
    Line* deserialize_one(const std::vector<uint8_t>& in, size_t& offset);
public:
    void add_line(Line* line);
    void insert_line(int index, Line* line);
    void delete_line(int index);
    Line* get_line_at(int index) const;
    void print() const;

    void append_textline(int line_index, std::string& app_text);
    void find_string_textline(int line_index, std::string& looking_for) const;
    void insert_at_textline(int line_index, std::string& str, int position);
    void replace_text_textline(int line_index, std::string& str, int position);
    void delete_text_textline(int line_index, int position, int amount_of_symbols);

    void copy_fragment(int line_index, int index, int count);
    void cut_fragment(int line_index, int index, int count);
    void copy_line(int line_index);
    void cut_line(int line_index);
    void paste_fragment(int line_index, int index);
    void paste_line(int line_index);

    std::vector<uint8_t> serialize() const;
    void deserialize(const std::vector<uint8_t>& in);
    ~Text();
};

#endif //ASSIGMENT4_TEXT_H
