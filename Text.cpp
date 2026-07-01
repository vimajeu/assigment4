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
    lines.insert(lines.begin() + index, line);
}

void Text::delete_line(int index) {
    lines.erase(lines.begin() + index);
}

void Text::replace_line(int index, Line *line) {
    delete_line(index);
    insert_line(index, line);
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
        std::cout << "This command only works for text type of line.";
        return "";
    }
    TextLine* temp = static_cast<TextLine *>(lines[line_index]);
    return temp->copy_fragment(position, am_of_symbs);
}

void Text::append_textline(int line_index, std::string& app_text) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line.";
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->append(app_text);
}
void Text::find_string_textline(int line_index, std::string& looking_for) const {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line.";
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->find_string(looking_for);
}
void Text::insert_at_textline(int line_index, std::string& str, int position) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line.";
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->insert_at(str, position);
}
void Text::replace_text_textline(int line_index, std::string& str, int position) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line.";
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->replace_text(str, position);
}
void Text::delete_text_textline(int line_index, int position, int amount_of_symbols) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line.";
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->delete_text(position, amount_of_symbols);
}

void Text::copy_fragment(int line_index, int index, int count) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line.";
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    text_buffer = t1->copy_fragment(index, count);
}

void Text::cut_fragment(int line_index, int index, int count) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line.";
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    text_buffer = t1->cut_fragment(index, count);
}

void Text::copy_line(int line_index) {
    delete line_buffer;
    line_buffer = lines[line_index]->clone();
}

void Text::cut_line(int line_index) {
    delete line_buffer;
    line_buffer = lines[line_index]->clone();
    delete_line(line_index);
}

void Text::paste_fragment(int line_index, int index) {
    if (lines[line_index]->getType() != LineType::Text) {
        std::cout << "This command only works for text type of line.";
        return;
    }
    if (text_buffer == "") {
        std::cout << "Buffer is empty.";
        return;
    }
    TextLine* t1 = static_cast<TextLine *>(lines[line_index]);
    t1->insert_at(text_buffer, index);
}
void Text::paste_line(int line_index) {
    if (line_buffer == nullptr) {
        std::cout << "Buffer is empty.";
        return;
    }
    insert_line(line_index, line_buffer->clone());
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
    delete line_buffer;
}
