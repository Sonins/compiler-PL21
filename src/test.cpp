#include <iostream>
#include <string>
#include <vector>

#include "global_item.hpp"

#define DEBUG

using std::vector;
using std::cout;
using std::endl;

extern grammar lang_grammar;
extern item _decls_;
extern item _vtype_;
extern item _slist_;
extern item _intdecl_;
extern vector<item> nonterminals;
int main() {
    cout << "first-- " << endl;
    for (auto non : nonterminals) {
        set<item> f = lang_grammar.first(non);
        cout << non.get_item_name() << " : ";
        for (auto i : f) {
            cout << i.get_item_name() << " ";
        }
        cout << endl;
    }

    cout << "follow-- " << endl;
    for (auto non : nonterminals) {
        set<item> f = lang_grammar.follow(non);
        cout << non.get_item_name() << " : ";
        for (auto i : f) {
            cout << i.get_item_name() << " ";
        }
        cout << endl;
    }
    
    
}