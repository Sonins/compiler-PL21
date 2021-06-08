#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>

using std::string;

enum class item_type {
  nonterminal = 0,
  terminal = 1,
};

class Item {
 public:
  Item() {}
  Item(string name, item_type type) : item_name(name), type(type) {
    this->__can_be_empty = false;
  }

  Item(string item_name, item_type type, bool emptyable)
      : item_name(item_name), type(type), __can_be_empty(emptyable) {}

  bool is_terminal() { return type == item_type::terminal; }

  bool is_nonterminal() { return type == item_type::nonterminal; }

  bool operator==(const Item &other) const {
    return item_name == other.item_name && this->type == other.type;
  }

  bool operator==(const string &str) { return item_name == str; }

  bool operator!=(const Item &other) const { return !(*this == other); }

  bool operator<(const Item &other) const {
    if (type < other.type) return true;
    if (type > other.type) return false;

    return item_name < other.item_name;
  }

  void set_name(string item_name) { this->item_name = item_name; }

  void set_type(item_type type) { this->type = type; }

  void set_value(string value) { this->item_value = value; }

  string get_item_name() const { return this->item_name; }

  bool can_be_empty() { return __can_be_empty; }

  void set_can_be_empty() { this->__can_be_empty = true; }

 private:
  string item_name;
  string item_value;
  item_type type;
  bool __can_be_empty;
};
#endif