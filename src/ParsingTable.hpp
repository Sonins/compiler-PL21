#ifndef PARSING_TABLE_HPP
#define PARSING_TABLE_HPP

#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <stack>

#include "Grammar.hpp"

using std::map;
using std::queue;
using std::set;
using std::string;
using std::vector;

class action;
class handler;
class state;
class parsing_table;

enum class action_type {
  shift = 0,
  reduce = 1,
};

class state {
 public:
  state();

  state(int state_number, vector<handler> &hand_set);

  map<Item, vector<handler>> possible_moves();

  bool contains_handlers(vector<handler> &h);

  void link_other_state(Item item, int other);

  int get_state_number() const;

  vector<handler> get_handler_set();

  void state_print();

  action find_action(Item item);

 private:
  int state_number;
  map<Item, action> act_map;
  vector<handler> handler_set;
  map<Item, vector<handler>> moves;
};

class action {
 public:
  action(action_type tp, int tar);

  bool is_shift();

  bool is_reduce();

  int get_target_state();

 private:
  action_type type;
  int target_state;
};

class handler {
 public:
  handler(Rule r, int dotidx, set<Item> lookahead);

  handler();

  bool operator==(handler &other);

  bool operator!=(handler &other);

  Item dot_item();

  set<Item> get_lookahead();

  vector<Item> get_production_rhs();

  int get_dotindex();

  void dot_moves();

  void print_handler();

 private:
  Rule handler_rule;
  int dotindex;
  set<Item> lookahead;
};



class parsing_table {
 public:
  parsing_table(std::map<Item, vector<Rule>> rmap);
  parsing_table();
  ~parsing_table();
  void printout_table();

 private:
  void processing_rules(std::map<Item, vector<Rule>> &rmap);

  vector<handler> generate_closure(std::map<Item, vector<Rule>> &rmap,
                                   vector<handler> &basic_handler);

  vector<state *> state_set;
};
#endif