#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "Item.hpp"

using std::set;
using std::stack;
using std::string;
using std::vector;

#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP
#define START_ITEM _prog_

extern Item _empty_;
extern Item _EOF_;
extern Item _prog_;

class Rule {
 public:
  Rule(Item &left, vector<Item> right) {
    this->left_hand = left;
    this->right_hand = right;

    if (right.size() > 0 && right[0] == _empty_) {
      left.set_can_be_empty();
    }
  }

  Rule() {}

  Item get_left_hand() { return left_hand; }

  vector<Item> get_right_hand() { return right_hand; }

  Item get_right_hand_first() { return right_hand[0]; }

  bool operator==(Rule &other) {
    if (other.get_left_hand() != this->get_left_hand()) return false;
    vector<Item> other_rhs = other.get_right_hand();
    if (other_rhs.size() != this->right_hand.size()) return false;

    for (int i = 0; i < other_rhs.size(); i++) {
      if (other_rhs[i] != this->right_hand[i]) return false;
    }

    return true;
  }

  bool operator!=(Rule &other) { return !(*this == other); }

  void rule_print() {
    std::cout << left_hand.get_item_name() << "->";
    for (auto it : right_hand) {
      std::cout << it.get_item_name() << " ";
    }
    std::cout << std::endl;
  }

 private:
  Item left_hand;
  vector<Item> right_hand;
};

class Grammar {
 public:
  Grammar(vector<Rule> &_rules, vector<Item> &_nonterminals,
          vector<Item> &_terminals)
      : rules(_rules), nonterminals(_nonterminals), terminals(_terminals) {
    int rule_size = rules.size();

    for (int i = 0; i < rule_size; i++) {
      auto find_result = rules_map.find(rules[i].get_left_hand());

      if (find_result != rules_map.end()) {
        find_result->second.push_back(rules[i]);
      } else {
        rules_map.insert(
            std::make_pair(rules[i].get_left_hand(), vector<Rule>{rules[i]}));
      }
    }

    init_first();
    init_follow();
  }

  set<Item> first(Item &_item) {
    if (_item.is_terminal()) return set<Item>{_item};
    return first_map.find(_item)->second;
  }

  set<Item> follow(Item &_item) {
    if (_item.is_terminal()) return set<Item>{};
    return follow_map.find(_item)->second;
  }

  std::map<Item, vector<Rule>> get_rules_map() { return rules_map; }

 private:
  void init_follow() {
    std::map<Item, int> depend;
    std::map<Item, vector<Item>> depend_list;

    for (auto i : nonterminals) {
      depend.insert(std::make_pair(i, 0));
      depend_list.insert(std::make_pair(i, vector<Item>{}));
      follow_map.insert(std::make_pair(i, set<Item>{}));
    }

    follow_map.find(START_ITEM)->second.insert(_EOF_);

    int rule_size = rules.size();
    for (auto r : rules) {
      vector<Item> rhs = r.get_right_hand();
      if (rhs[0] == _empty_) continue;
      Item lhs = r.get_left_hand();

      if (rhs[rhs.size() - 1].is_nonterminal()) {
        depend.find(rhs[rhs.size() - 1])->second++;
        depend_list.find(lhs)->second.push_back(rhs[rhs.size() - 1]);
      }

      // 원래는 empty case도 조사해야 하나, 주어진 문법에 해당 case가
      // 없다. 구현도 어려우므로 그냥 생략한다.

      for (int i = 0; i < rhs.size() - 1; i++) {
        link_first_follow(rhs[i], rhs[i + 1]);
      }
    }

    // topological sort 느낌으로 순회한다.

    stack<Item> st;

    for (auto i : depend) {
      if (i.second == 0) {
        st.push(i.first);
      }
    }

    while (!st.empty()) {
      Item it = st.top();
      st.pop();
      vector<Item> childs = depend_list.find(it)->second;
      for (auto i : childs) {
        link_follow_follow(it, i);
        depend.find(i)->second--;
        if (depend.find(i)->second == 0) st.push(i);
      }
    }
  }

  void link_first_follow(Item follow_item, Item first_item) {
    set<Item> followset;
    set<Item> firstset;

    if (follow_item.is_terminal()) return;

    followset = follow(follow_item);
    firstset = first(first_item);

    std::set_difference(
        firstset.begin(), firstset.end(), followset.begin(), followset.end(),
        std::inserter(follow_map.find(follow_item)->second,
                      follow_map.find(follow_item)->second.end()));
  }

  void link_follow_follow(Item parent_item, Item child_item) {
    set<Item> parentset;
    set<Item> childset;

    parentset = follow(parent_item);
    childset = follow(child_item);

    std::set_difference(
        parentset.begin(), parentset.end(), childset.begin(), childset.end(),
        std::inserter(follow_map.find(child_item)->second,
                      follow_map.find(child_item)->second.end()));
  }

  void init_first() {
    int nonterminals_size = nonterminals.size();

    for (int i = 0; i < nonterminals_size; i++) {
      Item nter = nonterminals[i];
      first_map.insert(make_pair(nter, first_search(nter)));
    }
  }

  set<Item> first_search(Item _item) {
    set<Item> result;

    if (_item.is_terminal()) {
      return set<Item>{_item};
    }

    if (rules_map.find(_item) == rules_map.end()) {
      return result;
    }

    stack<Item> st;
    set<Item> visit;
    st.push(_item);

    while (!st.empty()) {
      Item cur = st.top();
      st.pop();
      if (cur == _empty_) continue;

      if (cur.is_terminal())
        result.insert(cur);

      else if (visit.find(cur) == visit.end()) {
        visit.insert(cur);
        vector<Rule> corres_rules = rules_map.find(cur)->second;
        for (auto &i : corres_rules) {
          Item rhs_first = i.get_right_hand_first();
          st.push(rhs_first);

          // 만약 A->Bc 에서 B가 empty가 될 수 있으면, first(A)는 c도
          // 포함할 것이다. 다음은 그것을 처리한것.
          vector<Item> rhs = i.get_right_hand();
          if (rhs_first.can_be_empty() && rhs.size() >= 2) st.push(rhs[1]);
        }
      }
    }

    return result;
  }

  std::map<Item, set<Item>> first_map;
  std::map<Item, set<Item>> follow_map;
  std::map<Item, vector<Rule>> rules_map;
  vector<Rule> rules;
  vector<Item> nonterminals;
  vector<Item> terminals;
};

#endif