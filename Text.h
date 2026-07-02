//
// Created by ліна on 01.07.2026.
//

#ifndef ASSIGMENT4_TEXT_H
#define ASSIGMENT4_TEXT_H
#include <string>
#include "Line.h"
#include <vector>

class Command;
class Text {
    std::vector<Line*> lines;
    std::string text_buffer;
    std::vector<Command*> undoStack;
    std::vector<Command*> redoStack;
    Line* deserialize_one(const std::vector<uint8_t>& in, size_t& offset);
public:
    void execute_command(Command* c);
    void undo();
    void redo();

    void add_line(Line* line);
    void insert_line(int index, Line* line);
    void delete_line(int index);
    void toggle(int line_index);
    void print() const;

    std::string get_buffer();
    std::string get_text(int line_index, int position, int am_of_symbs);
    Line* get_line_at(int index) const;
    int lines_amount();

    void append_textline(int line_index, std::string& app_text);
    void find_string_textline(int line_index, std::string& looking_for) const;
    void insert_at_textline(int line_index, std::string& str, int position);
    void replace_text_textline(int line_index, std::string& str, int position);
    void delete_text_textline(int line_index, int position, int amount_of_symbols);

    void copy_fragment(int line_index, int index, int count);
    void cut_fragment(int line_index, int index, int count);
    void paste_fragment(int line_index, int index);

    std::vector<uint8_t> serialize() const;
    void deserialize(const std::vector<uint8_t>& in);
    ~Text();
};

#endif //ASSIGMENT4_TEXT_H
