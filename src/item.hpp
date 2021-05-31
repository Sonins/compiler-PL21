#include <string>
#include <regex>
#include <iostream>

using std::string;

#ifndef ITEM_HPP
#define ITEM_HPP
enum class item_type {
    nonterminal = 0,
    terminal = 1,
};

class item {
    public:
    item() {}
    item(string item_name, item_type type) {
        set_name(item_name);
        set_type(type);
        this->__can_be_empty = false;
    }

    item(string item_name, item_type type, bool emptyable) {
        set_name(item_name);
        set_type(type);
        if (emptyable)
            set_can_be_empty();
    }

    bool is_terminal() {
        return type == item_type::terminal;
    }

    bool is_nonterminal() {
        return type == item_type::nonterminal;
    }

    bool operator==(const item &other) const {
        return item_name == other.item_name && this->type == other.type;
    }

    bool operator==(const string &str) const {
        return item_name == str;
    }
    
    bool operator< (const item &other) const {
        if (type < other.type)
            return true;
        if (type > other.type)
            return false;

        return item_name < other.item_name;
    }

    void set_name(string item_name) {
        this->item_name = item_name;
    }

    void set_type(item_type type) {
        this->type = type;
    }

    string get_item_name() {
        return this->item_name;
    }

    bool can_be_empty() {
        return __can_be_empty;
    }

    void set_can_be_empty() {
        this->__can_be_empty = true;
    }

    private:
    
    string item_name;
    item_type type;
    bool __can_be_empty;
};

class regex_item : public item {
    public:
    regex_item(string regex_expr, item_type type) {
        try {
            std::regex re(regex_expr);
        } catch(const std::regex_error& e) {
            item(regex_expr, type);
            return;
        }
        set_name(regex_expr);
        set_type(type);
        item_regex = std::regex(regex_expr);
    }

    bool operator==(string& other) {
        return std::regex_match(other, item_regex);
    }
    
    private:
    std::regex item_regex;
};
#endif