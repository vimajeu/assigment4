//
// Created by ліна on 01.07.2026.
//

#ifndef ASSIGMENT4_COMMAND_H
#define ASSIGMENT4_COMMAND_H

#include <string>

#include "Text.h"

class Command {
public:
    virtual void redo() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class AddLine : public Command {
    Text* owner;
    Line* line;
public:
    AddLine(Text* t, Line* l) : owner(t), line(l) {
    }
    void redo() override;
    void undo() override;
};

class InsertLine : public Command {
    Text* owner;
    Line* line;
    int index;
public:
    InsertLine(Text* t, Line* l, int i) : owner(t), line(l), index(i) {
    }
    void redo() override;
    void undo() override;
};

class DeleteLine : public Command {
    Text* owner;
    Line* line;
    int index;
public:
    DeleteLine(Text* t, int i) : owner(t), index(i) {
        line = owner->get_line_at(index)->clone();
    }
    void redo() override;
    void undo() override;
};

class AppendTextLine : public Command {
    Text* owner;
    std::string text;
public:
    AppendTextLine(Text* o, const std::string& t) : owner(o), text(t) {
    }
    void redo() override;
    void undo() override;
};

class InsertText : public Command {
    Text* owner;
    std::string text;
    int line_index;
    int position;
public:
    InsertText(Text* o, const std::string& t, int i, int p) : owner(o), text(t), line_index(i), position(p) {
    }
    void redo() override;
    void undo() override;
};

class ReplaceText : public Command {
    Text* owner;
    std::string original_text;
    std::string new_text;
    int line_index;
    int position;
public:
    ReplaceText(Text* o, const std::string& nt, int i, int p) : owner(o), new_text(nt), line_index(i), position(p) {
        original_text = owner->get_text(line_index, position, new_text.size());
    }
    void redo() override;
    void undo() override;
};

class DeleteTextTextline : public Command {
    Text* owner;
    std::string text;
    int line_index;
    int position;
    int amount_to_delete;
public:
    DeleteTextTextline(Text* o, int i, int p, int d) : owner(o), line_index(i), position(p), amount_to_delete(d) {
        text = owner->get_text(line_index, position, amount_to_delete);
    }
    void redo() override;
    void undo() override;
};


#endif //ASSIGMENT4_COMMAND_H
