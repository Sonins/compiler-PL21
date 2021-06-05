#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "item.hpp"

using std::set;
using std::stack;
using std::string;
using std::vector;

#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP
#define START_ITEM _prog_

extern item _empty_;
extern item _EOF_;
extern item _prog_;

class rule {
   public:
    rule(item &left, vector<item> right) {
        this->left_hand = left;
        this->right_hand = right;
        if (right[0] == _empty_) left.set_can_be_empty();
    }

    rule() {
        
    }

    item get_left_hand() { return left_hand; }

    vector<item> get_right_hand() { return right_hand; }

    item get_right_hand_first() { return right_hand[0]; }

   private:
    item left_hand;
    vector<item> right_hand;
};

class grammar {
   public:
    grammar(vector<rule> &_rules, vector<item> &_nonterminals,
            vector<item> &_terminals)
        : rules(_rules), nonterminals(_nonterminals), terminals(_terminals) {
        int rule_size = rules.size();

        for (int i = 0; i < rule_size; i++) {
            auto find_result = rules_map.find(rules[i].get_left_hand());

            if (find_result != rules_map.end()) {
                find_result->second.push_back(rules[i]);
            } else {
                rules_map.insert(std::make_pair(rules[i].get_left_hand(),
                                                vector<rule>{rules[i]}));
            }
        }

        init_first();
        init_follow();
    }

    set<item> first(item &_item) {
        if (_item.is_terminal()) return set<item>{_item};
        return first_map.find(_item)->second;
    }

    set<item> follow(item &_item) {
        if (_item.is_terminal()) return set<item>{};
        return follow_map.find(_item)->second;
    }

    std::map<item, vector<rule>> get_rules_map() {
        return rules_map;
    }

   private:
    void init_follow() {
        std::map<item, int> depend;
        std::map<item, vector<item>> depend_list;

        for (auto i : nonterminals) {
            depend.insert(std::make_pair(i, 0));
            depend_list.insert(std::make_pair(i, vector<item>{}));
            follow_map.insert(std::make_pair(i, set<item>{}));
        }
        
        follow_map.find(START_ITEM)->second.insert(_EOF_);

        int rule_size = rules.size();
        for (auto r : rules) {
            vector<item> rhs = r.get_right_hand();
            if (rhs[0] == _empty_) continue;
            item lhs = r.get_left_hand();

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

        stack<item> st;

        for (auto i : depend) {
            if (i.second == 0) {
                st.push(i.first);
            }
        }

        while (!st.empty()) {
            item it = st.top();
            st.pop();
            vector<item> childs = depend_list.find(it)->second;
            for (auto i : childs) {
                link_follow_follow(it, i);
                depend.find(i)->second--;
                if (depend.find(i)->second == 0) st.push(i);
            }
        }
    }

    void link_first_follow(item follow_item, item first_item) {
        set<item> followset;
        set<item> firstset;

        if (follow_item.is_terminal()) return;

        followset = follow(follow_item);
        firstset = first(first_item);

        std::set_difference(
            firstset.begin(), firstset.end(), 
            followset.begin(), followset.end(),
            std::inserter(follow_map.find(follow_item)->second,
                          follow_map.find(follow_item)->second.end()));
    }

    void link_follow_follow(item parent_item, item child_item) {
        set<item> parentset;
        set<item> childset;

        parentset = follow(parent_item);
        childset = follow(child_item);

        std::set_difference(
            parentset.begin(), parentset.end(), 
            childset.begin(), childset.end(),
            std::inserter(follow_map.find(child_item)->second,
                          follow_map.find(child_item)->second.end()));
    }

    void init_first() {
        int nonterminals_size = nonterminals.size();

        for (int i = 0; i < nonterminals_size; i++) {
            item nter = nonterminals[i];
            first_map.insert(make_pair(nter, first_search(nter)));
        }
    }

    set<item> first_search(item _item) {
        set<item> result;

        if (_item.is_terminal()) {
            return set<item>{_item};
        }

        if (rules_map.find(_item) == rules_map.end()) {
            return result;
        }

        stack<item> st;
        set<item> visit;
        st.push(_item);

        while (!st.empty()) {
            item cur = st.top();
            st.pop();
            if (cur == _empty_) continue;

            if (cur.is_terminal())
                result.insert(cur);

            else if (visit.find(cur) == visit.end()) {
                visit.insert(cur);
                vector<rule> corres_rules = rules_map.find(cur)->second;
                for (auto &i : corres_rules) {
                    item rhs_first = i.get_right_hand_first();
                    st.push(rhs_first);

                    // 만약 A->Bc 에서 B가 empty가 될 수 있으면, first(A)는 c도
                    // 포함할 것이다. 다음은 그것을 처리한것.
                    vector<item> rhs = i.get_right_hand();
                    if (rhs_first.can_be_empty() && rhs.size() >= 2)
                        st.push(rhs[1]);
                }
            }
        }

        return result;
    }

    std::map<item, set<item>> first_map;
    std::map<item, set<item>> follow_map;
    std::map<item, vector<rule>> rules_map;
    vector<rule> rules;
    vector<item> nonterminals;
    vector<item> terminals;
};

#endif