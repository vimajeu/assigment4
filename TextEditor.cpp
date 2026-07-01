//
// Created by ліна on 30.06.2026.
//

#include "Command.h"
#include "TextEditor.h"

#include <fstream>

#include "CheckListLine.h"
#include "ContactInfoLine.h"
#include "TextLine.h"

void TextEditor::show_menu() {
    std::cout << "1. Add line\n" << std::endl;
    std::cout << "2. Insert line\n" << std::endl;
    std::cout << "3. Delete line\n" << std::endl;
    std::cout << "4. Print\n" << std::endl;
    std::cout << "5. Append line\n" << std::endl;
    std::cout << "6. Find text\n" << std::endl;
    std::cout << "7. Insert text\n" << std::endl;
    std::cout << "8. Replace text\n" << std::endl;
    std::cout << "9. Delete text\n" << std::endl;
    std::cout << "10. Copy text\n" << std::endl;
    std::cout << "11. Cut text\n" << std::endl;
    std::cout << "12. Paste text\n" << std::endl;
    std::cout << "13. Toggle checklist item\n" << std::endl;
    std::cout << "14. Save to file\n" << std::endl;
    std::cout << "15. Load from file\n" << std::endl;
    std::cout << "16. Undo\n" << std::endl;
    std::cout << "17. Redo\n" << std::endl;
    std::cout << "18. Encrypt\n" << std::endl; //!!!!!!!!!!!!!!!!!!!!!
    std::cout << "19. Decrypt\n" << std::endl; //!!!!!!!!!!!!!!!!!!!!!
    std::cout << "0. Exit\n" << std::endl;
}

void TextEditor::handle_command(int choice) {
    switch (choice) {
        case 1: {
            int text_type;
            std::cout << "1. Text" << std::endl;
            std::cout << "2. Checklist" << std::endl;
            std::cout << "3. Contact line" << std::endl;
            std::cout << "Choose line type: " << std::endl;
            std::cin >> text_type;
            std::cin.ignore();
            switch (text_type) {
                case 1: {
                    std::string input;
                    std::cout << "Enter text: " << std::endl;
                    std::getline(std::cin, input);
                    Command* c = new AddLine(&text, new TextLine(input));
                    text.execute_command(c);
                    break;
                }
                case 2: {
                    std::string input;
                    std::cout << "Enter text: " << std::endl;
                    std::getline(std::cin, input);
                    Command* c = new AddLine(&text, new ChecklistLine(input, false));
                    text.execute_command(c);
                    break;
                }
                case 3: {
                    std::string name, surname, email;
                    std::cout << "Enter name: " << std::endl;
                    std::getline(std::cin, name);
                    std::cout << "Enter surname: " << std::endl;
                    std::getline(std::cin, surname);
                    std::cout << "Enter email: " << std::endl;
                    std::getline(std::cin, email);
                    Command* c = new AddLine(&text, new ContactInfoLine(name, surname, email));
                    text.execute_command(c);
                    break;
                }
                default:
                    std::cout << "Invalid line type." << std::endl;
                    break;
            }
            break;
        }
        case 2: {
            int text_type;
            int index;
            std::cout << "1. Text\n" << std::endl;
            std::cout << "2. Checklist\n" << std::endl;
            std::cout << "3. Contact line\n" << std::endl;
            std::cout << "Choose line type: \n" << std::endl;
            std::cin >> text_type;
            std::cin.ignore();

            std::cout << "Enter index: \n" << std::endl;
            std::cin >> index;
            std::cin.ignore();
            switch (text_type) {
                case 1: {
                    std::string input;
                    std::cout << "Enter text: " << std::endl;
                    std::getline(std::cin, input);
                    Command* c = new InsertLine(&text, new TextLine(input), index);
                    text.execute_command(c);
                    break;
                }
                case 2: {
                    std::string input;
                    std::cout << "Enter text: " << std::endl;
                    std::getline(std::cin, input);
                    Command* c = new InsertLine(&text, new ChecklistLine(input, false), index);
                    text.execute_command(c);
                    break;
                }
                case 3: {
                    std::string name, surname, email;
                    std::cout << "Enter name: " << std::endl;
                    std::getline(std::cin, name);
                    std::cout << "Enter surname: " << std::endl;
                    std::getline(std::cin, surname);
                    std::cout << "Enter email: " << std::endl;
                    std::getline(std::cin, email);
                    Command* c = new InsertLine(&text, new ContactInfoLine(name, surname, email), index);
                    text.execute_command(c);
                    break;
                }
                default:
                    std::cout << "Invalid line type." << std::endl;
                    break;
            }
            break;
        }
        case 3: {
            int index;
            std::cout << "Enter index: " << std::endl;
            std::cin >> index;
            std::cin.ignore();
            Command* c = new DeleteLine(&text, index);
            text.execute_command(c);
            break;
        }
        case 4: {
            text.print();
            break;
        }
        case 5: {
            std::string append_text;
            int index;
            std::cout << "Enter text to append: \n" << std::endl;
            std::getline(std::cin, append_text);
            std::cout << "Enter line index: \n" << std::endl;
            std::cin >> index;
            std::cin.ignore();

            Command* c = new AppendTextLine(&text, append_text, index);
            text.execute_command(c);
            break;
        }
        case 6: {
            std::string look_for;
            int line_index;
            std::cout << "Enter text to append: \n" << std::endl;
            std::getline(std::cin, look_for);
            std::cout << "Enter line index: \n" << std::endl;
            std::cin >> line_index;
            std::cin.ignore();
            text.find_string_textline(line_index, look_for);
            break;
        }
        case 7: {
            std::string input;
            int line_index;
            int position;
            std::cout << "Enter text to append: \n" << std::endl;
            std::getline(std::cin, input);
            std::cout << "Enter line index: \n" << std::endl;
            std::cin >> line_index;
            std::cin.ignore();
            std::cout << "Enter position: \n" << std::endl;
            std::cin >> position;
            std::cin.ignore();
            Command* c = new InsertText(&text, input, line_index, position);
            text.execute_command(c);
            break;
        }
        case 8: {
            std::string input;
            int line_index;
            int position;
            std::cout << "Enter text to append: \n" << std::endl;
            std::getline(std::cin, input);
            std::cout << "Enter line index: \n" << std::endl;
            std::cin >> line_index;
            std::cin.ignore();
            std::cout << "Enter position: \n" << std::endl;
            std::cin >> position;
            std::cin.ignore();
            Command* c = new ReplaceText(&text, input, line_index, position);
            text.execute_command(c);
            break;
        }
        case 9: {
            int line_index;
            int position;
            int am_to_delete;
            std::cout << "Enter line index: \n" << std::endl;
            std::cin >> line_index;
            std::cin.ignore();
            std::cout << "Enter position: \n" << std::endl;
            std::cin >> position;
            std::cin.ignore();
            std::cout << "Enter amount to delete: \n" << std::endl;
            std::cin >> am_to_delete;
            std::cin.ignore();
            Command* c = new DeleteTextTextline(&text, line_index, position, am_to_delete);
            text.execute_command(c);
            break;
        }
        case 10: {
            int line_index;
            int position;
            int amount;
            std::cout << "Enter line index: \n" << std::endl;
            std::cin >> line_index;
            std::cin.ignore();
            std::cout << "Enter position: \n" << std::endl;
            std::cin >> position;
            std::cin.ignore();
            std::cout << "Enter amount to delete: \n" << std::endl;
            std::cin >> amount;
            std::cin.ignore();
            text.copy_fragment(line_index, position, amount);
            break;
        }
        case 11: {
            int line_index, position, amount;
            std::cout << "Enter line index: " << std::endl;
            std::cin >> line_index;
            std::cin.ignore();
            std::cout << "Enter position: " << std::endl;
            std::cin >> position;
            std::cin.ignore();
            std::cout << "Enter amount to cut: " << std::endl;
            std::cin >> amount;
            std::cin.ignore();

            text.copy_fragment(line_index, position, amount);
            Command* c = new DeleteTextTextline(&text, line_index, position, amount);
            text.execute_command(c);
            break;
        }
        case 12: {
            int line_index;
            int position;
            std::cout << "Enter line index: \n" << std::endl;
            std::cin >> line_index;
            std::cin.ignore();
            std::cout << "Enter position: \n" << std::endl;
            std::cin >> position;
            std::cin.ignore();
            Command* c = new InsertText(&text, text.get_buffer(), line_index, position);
            text.execute_command(c);
            break;
        }
        case 13: {
            int line_index;
            std::cout << "Enter line index: \n" << std::endl;
            std::cin >> line_index;
            std::cin.ignore();
            text.toggle(line_index);
            break;
        }
        case 14: {
            std::string filename;
            std::cout << "Enter file name for saving: " << std::endl;
            std::getline(std::cin, filename);

            std::vector<uint8_t> data = text.serialize();

            std::ofstream file(filename, std::ios::binary);
            if (!file) {
                std::cout << "Error opening file for writing." << std::endl;
                break;
            }
            file.write(reinterpret_cast<const char*>(data.data()), data.size());
            file.close();

            std::cout << "Text has been saved successfully" << std::endl;
            break;
        }
        case 15: {
            std::string filename;
            std::cout << "Enter file name for loading: " << std::endl;
            std::getline(std::cin, filename);

            std::ifstream file(filename, std::ios::binary);
            if (!file) {
                std::cout << "Error opening file for reading." << std::endl;
                break;
            }

            std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                                        std::istreambuf_iterator<char>());
            file.close();

            text.deserialize(data);
            std::cout << "Text has been loaded successfully" << std::endl;
            break;
        }
        case 16: {
            text.undo();
            break;
        }
        case 17: {
            text.redo();
            break;
        }
    }
}

void TextEditor::run() {
    int choice = -1;
    while (choice != 0) {
        show_menu();
        std::cout << "Choose command: \n" << std::endl;
        std::cin >> choice;
        std::cin.ignore();
        handle_command(choice);
    }
}
