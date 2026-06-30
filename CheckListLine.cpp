//
// Created by ліна on 30.06.2026.
//

#include "CheckListLine.h"
void ChecklistLine::toggle() {
    checked = !checked;
}

LineType ChecklistLine::getType() const {
    return LineType::CheckList;
}

void ChecklistLine::serialize(std::vector<uint8_t>& out) const {
    out.push_back(static_cast<uint8_t>(getType()));
    uint32_t length = static_cast<uint32_t>(item.size());
    for (int i = 0; i < 4; i++) {
        out.push_back(static_cast<uint8_t>(length >> (i * 8) & 0xFF));
    }

    for (char c : item) {
        out.push_back(static_cast<uint8_t>(c));
    }

    out.push_back(checked);
}

Line* ChecklistLine::clone() const {
    return new ChecklistLine(item, checked);
}

ChecklistLine* ChecklistLine::deserialize(const std::vector<uint8_t>& in, size_t& offset) {
    uint32_t length = 0;
    for (int i = 0; i < 4; i++) {
        length |= static_cast<uint32_t>(in[offset + i]) << (i * 8);
    }
    offset += 4;

    std::string data(in.begin() + offset, in.begin() + offset + length);
    offset += length;

    bool ch = in[offset];
    offset += 1;
    return new ChecklistLine(data, ch);
}
