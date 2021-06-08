#include "ParsingTable.hpp"

extern Item _EOF_;
extern Item _empty_;
extern Grammar lang_grammar;

using std::map;
using std::queue;
using std::set;
using std::string;
using std::vector;
using std::stack;

action::action(action_type tp, state tar) : type(tp), target_state(tar) {}

bool action::is_shift() { return type == action_type::shift; }

bool action::is_reduce() { return type == action_type::reduce; }

state action::get_target_state() { return target_state; }

/**
 * Handler implementation
 * 
 * handler는 DFA 한 노드 안에 있는 production을 의미함.
 * prog -> word. ( ) block, $ 이런거.
 * 
*/

handler::handler() {}

handler::handler(Rule r, int dotidx, set<Item> lookahead) 
    : handler_rule(r), dotindex(dotidx), lookahead(lookahead) {

  if (handler_rule.get_right_hand_first() == _empty_) {
    Item lhs = r.get_left_hand();
    Rule rule(lhs, vector<Item>{});
    handler_rule = rule;
  }
}

bool handler::operator==(handler &other) {
  if (other.handler_rule != this->handler_rule) return false;
  if (other.dotindex != this->dotindex) return false;

  for (auto it : this->lookahead) {
    if (other.lookahead.find(it) == other.lookahead.end()) return false;
  }

  for (auto it : other.lookahead) {
    if (this->lookahead.find(it) == this->lookahead.end()) return false;
  }

  return true;
}

bool handler::operator!=(handler &other) { return !(*this == other); }

Item handler::dot_item() {
  vector<Item> rhs = handler_rule.get_right_hand();
  if (dotindex == rhs.size()) {
    return _EOF_;
  }
  return rhs[dotindex];
}

set<Item> handler::get_lookahead() { return lookahead; }

vector<Item> handler::get_production_rhs() {
  return handler_rule.get_right_hand();
}

int handler::get_dotindex() { return dotindex; }

void handler::dot_moves() {
  if (dotindex < handler_rule.get_right_hand().size())
    dotindex++;
}

void handler::print_handler() {
  Item lhs = handler_rule.get_left_hand();
  vector<Item> rhs = handler_rule.get_right_hand();

  std::cout << "\t" << lhs.get_item_name() << "->";
  for (int i = 0; i < rhs.size(); i++) {
    if (i == dotindex)
      std::cout << ".";
    std::cout << rhs[i].get_item_name() << " ";
  }
  if (dotindex == rhs.size())
    std::cout << ".";
  
  std::cout << ", ";

  for (auto it : lookahead)
    std::cout << it.get_item_name() << "/";

  std::cout << std::endl;
}

/**
 * State implementation.
 * 강의 교안에 보면 나오는 state와 같음.
 * DFA에서 한 노드에 해당함.
*/

state::state() {}

state::state(int state_number, vector<handler> &hand_set)
    : state_number(state_number), handler_set(hand_set) {
  // initiaiizing possible moves
  for (handler hand : handler_set) {
    Item it = hand.dot_item();
    if (moves.find(it) == moves.end()) {
      moves.insert(std::make_pair(it, vector<handler>{hand}));
    } else {
      moves.find(it)->second.push_back(hand);
    }
  }
}

map<Item, vector<handler>> state::possible_moves() { return moves; }

int state::get_state_number() const { return state_number; }

vector<handler> state::get_handler_set() { return handler_set; }

bool state::contains_handlers(vector<handler> &h) {
  bool flag = false;
  for (auto query_handler : h) {
    flag = false;
    for (auto contained_handler : handler_set) {
      if (query_handler == contained_handler) {
        flag = true;
        break;
      }
    }

    if (!flag) return false;
  }
  
  return true;
}

void state::link_other_state(Item item, state &other) {
  action act(action_type::shift, other);
  if (act_map.find(item) != act_map.end()) {
    fprintf(stderr, "confilct may have occurred\n");
    return;  // 실제로는 이런일이 일어나면 안됨. shift shift conflict?
  }
  act_map.insert(std::make_pair(item, act));
}

void state::state_print() {
  std::cout << state_number;
  for (auto h : handler_set) {
    h.print_handler();
  }
  std::cout << std::endl;
}

action state::find_action(Item item) {
  if (act_map.find(item) != act_map.end()) {
    return act_map.find(item)->second;
  } else {
    vector<handler> empty_set = {};
    return action(action_type::shift, state(-1, empty_set));
  }
}

/**
 * parsing_table
*/



parsing_table::parsing_table(std::map<Item, vector<Rule>> rmap) {
  processing_rules(rmap);
  std::sort(state_set.begin(), state_set.end(), [](const state& ls, const state& rs) {
    return ls.get_state_number() < rs.get_state_number();
  });
}

void parsing_table::processing_rules(std::map<Item, vector<Rule>> &rmap) {

  // state zero initialize.
  int state_num = 0;
  handler basic_handler(rmap.find(START_ITEM)->second[0], 0,
                        lang_grammar.follow(START_ITEM));
  vector<handler> hand_set;
  hand_set = vector<handler>{basic_handler};
  hand_set = generate_closure(rmap, hand_set);

  state cur_state(state_num++, hand_set);

  // DO BFS.
  stack<state> q;
  q.push(cur_state);

  while (!q.empty()) {
    cur_state = q.top();
    q.pop();
    state_set.push_back(cur_state);
    /**
     * moves에는 현재 state의 이동 가능 목록임.
     * 예를 들어, 어떤 state가 A->.B B->.CD C->.e C->.d 라고 한다면
     * moves 안에는 {B, A->.B}, {C, B->.CD}, {e, C->.e}, {d, C->.d}가 있음.
    */

    map<Item, vector<handler>> moves = cur_state.possible_moves();

    bool another_state_exist = false;
    for (auto it : moves) {
      another_state_exist = false;
      hand_set = it.second;

      vector<handler> new_hand_set;

      // dot moves for new state.
      for (auto hndlr : hand_set) {
        hndlr.dot_moves();
        new_hand_set.push_back(hndlr);
      }

      for (auto st : state_set) {
        if (st.contains_handlers(new_hand_set)) {
          // if new state already exist.
          cur_state.link_other_state(it.first, st);
          another_state_exist = true;
          break;
        }
      }

      if (another_state_exist) continue;

      hand_set = generate_closure(rmap, new_hand_set);
      
      state new_state(state_num++, hand_set);
      cur_state.link_other_state(it.first, new_state);
      q.push(new_state);
    }
  }
}

vector<handler> parsing_table::generate_closure(
    std::map<Item, vector<Rule>> &rmap, vector<handler> &basic_handler) {
  vector<handler> result;

  queue<handler> q;
  for (auto hndlr : basic_handler) {
    q.push(hndlr);
  }
  // 결국 중복을 어떻게 처리할 것인지 고민을 해봐야됨.
  // dotitem 비교로 하는중인데 같은 state이 여러개 나오네?? 왜지??
  set<Item> visit;
  handler cur_handler;

  while (!q.empty()) {
    cur_handler = q.front();
    q.pop();
    Item dot_item = cur_handler.dot_item();
    result.push_back(cur_handler);
    if (visit.find(dot_item) != visit.end())
      continue;
    visit.insert(dot_item);

    if (dot_item.is_terminal()) {
      continue;
    }

    vector<Item> production_rhs = cur_handler.get_production_rhs();
    int dotindex = cur_handler.get_dotindex();

    // get lookahead set for new handler.
    handler new_handler;
    set<Item> lookahead;

    if (dotindex == production_rhs.size() - 1)
      lookahead = cur_handler.get_lookahead();
    
    for (int i = 1; i < production_rhs.size() - dotindex; i++) {
      set<Item> first_set = lang_grammar.first(production_rhs[dotindex + i]);
      std::set_difference(first_set.begin(), first_set.end(), lookahead.begin(),
                          lookahead.end(),
                          std::inserter(lookahead, lookahead.end()));

      if (!production_rhs[dotindex + i].can_be_empty()) break;
    }
    
    // Rule 묶음을 구하고 그걸로 handler를 새로 만듬.
    vector<Rule> derived_rules = rmap.find(dot_item)->second;
    for (auto r : derived_rules) {
      new_handler = handler(r, 0, lookahead);
      q.push(new_handler);
    }
  }
  return result;
}

void parsing_table::printout_table() {
  for (auto st : state_set) {
    st.state_print();
  }
  extern vector<Item> terminals;
  for (auto it : terminals) {
    std::cout << "\t" << it.get_item_name();
  }
  std::cout << std::endl;

  for (auto st : state_set) {
    std::cout << st.get_state_number();
    for (auto it : terminals) {
      action act =st.find_action(it);
      if (act.get_target_state().get_state_number() == -1) {
        std::cout << "\t";
        continue;
      }
      
        std::cout << "\tS" << act.get_target_state().get_state_number();
    }
    std::cout << std::endl;
  }
}