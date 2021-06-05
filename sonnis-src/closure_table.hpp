#include <hash_map>
#include <string>
#include <vector>
#include <queue>
#include <map>

#include "grammar.hpp"

extern grammar lang_grammar;

using std::hash_map;
using std::string;
using std::vector;
using std::queue;

enum class action_type {
    shift = 0,
    reduce = 1,
};

class action {
   public:
    action(action_type tp, int tar) : type(tp), target_state(tar) {}
    bool is_shift() { return type == action_type::shift; }

    bool is_reduce() { return type == action_type::reduce; }

    int get_target_state() { return target_state; }

   private:
    action_type type;
    int target_state;
};

class _goto {
   public:
    _goto(int tar) : target_state(tar) {}

    int get_target_state() { return target_state; }

   private:
    int target_state;
};

class handler {
    public:

    handler() { }

    handler(rule &r, int cur, set<item> &lookahead)
    : handler_rule(r), dotindex(cur), lookahead(lookahead){

    }

    private:
    rule handler_rule;
    int dotindex;
    set<item> lookahead;
};

class state { 
    public:

    state(vector<handler> &hand_set)
    : handler_set(hand_set) {

    }
    

    private:
    std::hash_map<item, action> act_map;
    std::hash_map<item, _goto> goto_map;
    vector<handler> handler_set;

};

class closure_table {
   public:
    closure_table(std::map<item, vector<rule>> &rmap) {
        processing_rules(rmap);
    }

   private:
    void processing_rules(std::map<item, vector<rule>> &rmap) {

        int state_num;

        vector<handler> hand_set;
        hand_set = generate_handlers(rmap, rmap.find(START_ITEM)->second[0], 0);
        state_set.push_back(state(hand_set));

    }

    vector<handler> generate_handlers(std::map<item, vector<rule>> &rmap, vector<rule>& base_rule, vector<int> dotindex) {
        
        vector<handler> base_h;
        for (int i = 0; i < base_rule.size(); i++) {
            set<item> lookahead_set = lang_grammar.follow(base_rule[i].get_left_hand());
            base_h.push_back(handler(base_rule[i], dotindex[i], lookahead_set));
        }

        vector<handler> result;
        std::copy(base_h.begin(), base_h.end(), result.begin());

        

        set<item> visit;
        queue<item> q;
        q.push(rhs[dotindex]);

        item cur;
        while (!q.empty()) {
            cur = q.front();
            q.pop();

            vector<rule> cur_rules = rmap.find(cur)->second;
            for (auto r : cur_rules) {
                result.push_back(handler(r, 0, lang_grammar.follow(cur)));
                item rhs_first = r.get_right_hand_first();
                if (rhs_first.is_nonterminal())
                    q.push(rhs_first);
            }
        }

        return result;
    }
    vector<state> state_set;
};