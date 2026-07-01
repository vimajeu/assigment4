//
// Created by ліна on 01.07.2026.
//

#include "Text.h"
#include <string>
#include "CheckListLine.h"
#include "ContactInfoLine.h"
#include "TextLine.h"

void Text::add_line(Line* line) {
    lines.push_back(line);
}

void Text::insert_line(int index, Line* line) {
    if (index < 0 || index > static_cast<int>(lines.size())) {
        std::cout << "Index out of range\n" << std::endl;
        return;
    }
    lines.insert(lines.begin() + index, line);
}

void Text::delete_line(int index) {
    if (index < 0 || index > static_cast<int>(lines.size())) {
        std::cout << "Index out of range\n" << std::endl;
        return;
    }
    lines.erase(lines.begin() + index);
}

Line* Text::get_line_at(int index) const {
    return lines[index];
}

void Text::print() const {
    for (auto line : lines) {
        line->print();
    }
}

int Text::lines_amount() {
    return lines.size();
}

std::string Text::get_text(int line_index, int position, int am_of_symbs) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line." << std::endl;
        return "";
    }
    TextLine* temp = static_cast<TextLine *>(lines[line_index]);
    return temp->copy_fragment(position, am_of_symbs);
}

void Text::append_textline(int line_index, std::string& app_text) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line." << std::endl;
        return;
    }
    if (line_index < 0 || line_index > static_cast<int>(lines.size())) {
        std::cout << "Index out of range\n" << std::endl;
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->append(app_text);
}
void Text::find_string_textline(int line_index, std::string& looking_for) const {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line." << std::endl;
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->find_string(looking_for);
}
void Text::insert_at_textline(int line_index, std::string& str, int position) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line." << std::endl;
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->insert_at(str, position);
}
void Text::replace_text_textline(int line_index, std::string& str, int position) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line." << std::endl;
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->replace_text(str, position);
}
void Text::delete_text_textline(int line_index, int position, int amount_of_symbols) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line." << std::endl;
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->delete_text(position, amount_of_symbols);
}

void Text::copy_fragment(int line_index, int index, int count) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line." << std::endl;
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    text_buffer = t1->copy_fragment(index, count);
}

void Text::cut_fragment(int line_index, int index, int count) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line." << std::endl;
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    text_buffer = t1->cut_fragment(index, count);
}


void Text::paste_fragment(int line_index, int index) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line." << std::endl;
        return;
    }
    if (text_buffer == "") {
        std::cout << "Buffer is empty." << std::endl;
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->insert_at(text_buffer, index);
}

std::vector<uint8_t> Text::serialize() const {
    std::vector<uint8_t> result;
    for (auto line : lines) {
        line->serialize(result);
    }
    return result;
}

Line* Text::deserialize_one(const std::vector<uint8_t>& in, size_t& offset) {
    LineType type = static_cast<LineType>(in[offset]);
    offset++;
    if (type == LineType::Text) {
        return TextLine::deserialize(in, offset);
    }
    if (type == LineType::CheckList) {
        return ChecklistLine::deserialize(in, offset);
    }
    if (type == LineType::ContactInfo) {
        return ContactInfoLine::deserialize(in, offset);
    }
    std::cout << "Error: unknown line type" << std::endl;
    return nullptr;
}

void Text::deserialize(const std::vector<uint8_t>& in) {
    for (auto line : lines) {
        delete line;
    }
    lines.clear();

    size_t offset = 0;
    while (offset < in.size()) {
        Line* line = deserialize_one(in, offset);
        if (line == nullptr) break;
        lines.push_back(line);
    }
}

Text::~Text() {
    for (auto line : lines) {
        delete line;
    }
    for (auto c : undoStack) {
        delete c;
    }
    for (auto c : redoStack) {
        delete c;
    }
}

void Text::execute_command(Command* c) {
    c->redo();
    undoStack.push_back(c);
    for (auto command : redoStack) {
        delete command;
    }
    redoStack.clear();
}

void Text::undo() {
    if (undoStack.empty()) {
        std::cout << "No commands to undo." << std::endl;
        return;
    }
    Command* c = undoStack.back();
    c->undo();
    redoStack.push_back(c);
    undoStack.pop_back();
}

void Text::redo() {
    if (redoStack.empty()) {
        std::cout << "No commands to redo." << std::endl;
        return;
    }
    Command* c = redoStack.back();
    c->redo();
    undoStack.push_back(c);
    redoStack.pop_back();
}

void Text::toggle(int line_index) {
    if (lines[line_index]->getType() != LineType::CheckList) {
        std::cout << "This command only works for chechlist type of line." << std::endl;
        return;
    }
    ChecklistLine* t1 = static_cast<ChecklistLine *>(lines[line_index]);
    t1->toggle();
}

std::string Text::get_buffer() {
    return text_buffer;
}
