//
// Created by ліна on 01.07.2026.
//

#include "Command.h"
#include "Text.h"

void AddLine::undo() {
    owner->delete_line(owner->lines_amount() - 1);
}

void AddLine::redo() {
    owner->add_line(line->clone());
}

void InsertLine::undo() {
    owner->delete_line(index);
}

void InsertLine::redo() {
    owner->insert_line(index, line->clone());
}

void DeleteLine::undo() {
    owner->insert_line(index, line->clone());
}

void DeleteLine::redo() {
    delete line;
    line = owner->get_line_at(index);
    owner->delete_line(index);
}

void AppendTextLine::undo() {
    int cur_line = owner->lines_amount() - 1;
    owner->delete_text_textline(cur_line, owner->get_line_at(cur_line)->get_length() - text.size(), text.size());
}

void AppendTextLine::redo() {
    int cur_line = owner->lines_amount() - 1;
    owner->append_textline(cur_line, text);
}

void InsertText::undo() {
    owner->delete_text_textline(line_index, position, text.size());
}

void InsertText::redo() {
    owner->insert_at_textline(line_index, text, position);
}

void ReplaceText::undo() {
    owner->delete_text_textline(line_index, position, new_text.size());
    owner->insert_at_textline(line_index, original_text, position);
}

void ReplaceText::redo() {
    owner->delete_text_textline(line_index, position, original_text.size());
    owner->insert_at_textline(line_index, new_text, position);
}

void DeleteTextTextline::undo() {
    owner->insert_at_textline(line_index, text, position);
}

void DeleteTextTextline::redo() {
    owner->delete_text_textline(line_index, position, amount_to_delete);
}
