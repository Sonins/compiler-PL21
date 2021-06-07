#include <vector>

#include "Grammar.hpp"
#include "Item.hpp"

using std::vector;

Item _prog_("#prog", item_type::nonterminal);
Item _decls_("#decls", item_type::nonterminal);
Item _decl_("#decl", item_type::nonterminal);
Item _vtype_("#vtype", item_type::nonterminal);
Item _block_("#block", item_type::nonterminal);
Item _slist_("#slist", item_type::nonterminal);
Item _stat_("#stat", item_type::nonterminal);
Item _cond_("#cond", item_type::nonterminal);
Item _expr_("#expr", item_type::nonterminal);
Item _fact_("#fact", item_type::nonterminal);
Item _word_("#word", item_type::nonterminal);
Item _num_("#num", item_type::nonterminal);

Item _propen_("(", item_type::terminal);
Item _prclose_(")", item_type::terminal);
Item _brk_(";", item_type::terminal);
Item _bopen_("{", item_type::terminal);
Item _bclose_("}", item_type::terminal);
Item _intdecl_("int", item_type::terminal);
Item _chardecl_("char", item_type::terminal);
Item _if_("IF", item_type::terminal);
Item _then_("THEN", item_type::terminal);
Item _else_("ELSE", item_type::terminal);
Item _eq_("=", item_type::terminal);
Item _exit_("EXIT", item_type::terminal);
Item _lgreater_(">", item_type::terminal);
Item _plus_("+", item_type::terminal);
Item _word_term_("word", item_type::terminal);
Item _num_term_("num", item_type::terminal);

Item _empty_("000", item_type::terminal);
Item _EOF_("$", item_type::terminal);

// empty result should be first!
vector<Rule> rule_list = {
    Rule(_decls_, vector<Item>{_empty_}),
    Rule(_vtype_, vector<Item>{_empty_}),
    Rule(_block_, vector<Item>{_empty_}),
    Rule(_stat_, vector<Item>{_empty_}),
    Rule(_prog_, vector<Item>{_word_, _propen_, _prclose_, _block_}),
    Rule(_decls_, vector<Item>{_decls_, _decl_}),
    Rule(_decl_, vector<Item>{_vtype_, _word_, _brk_}),
    Rule(_vtype_, vector<Item>{_intdecl_}),
    Rule(_vtype_, vector<Item>{_chardecl_}),
    Rule(_block_, vector<Item>{_bopen_, _decls_, _slist_, _bclose_}),
    Rule(_slist_, vector<Item>{_slist_, _stat_}),
    Rule(_slist_, vector<Item>{_stat_}),
    Rule(_stat_, vector<Item>{_if_, _cond_, _then_, _else_, _block_}),
    Rule(_stat_, vector<Item>{_word_, _eq_, _expr_, _brk_}),
    Rule(_stat_, vector<Item>{_exit_, _expr_, _brk_}),
    Rule(_cond_, vector<Item>{_expr_, _lgreater_, _expr_}),
    Rule(_expr_, vector<Item>{_expr_, _plus_, _fact_}),
    Rule(_expr_, vector<Item>{_fact_}),
    Rule(_fact_, vector<Item>{_num_}),
    Rule(_fact_, vector<Item>{_word_}),
    Rule(_word_, vector<Item>{_word_term_}),
    Rule(_num_, vector<Item>{_num_term_})};

vector<Item> terminals = {_propen_,   _prclose_, _brk_,       _bopen_,
                          _bclose_,   _intdecl_, _chardecl_,  _if_,
                          _then_,     _else_,    _eq_,        _exit_,
                          _lgreater_, _plus_,    _word_term_, _num_term_};

vector<Item> nonterminals = {_prog_, _decls_, _decl_, _vtype_, _block_, _slist_,
                             _stat_, _cond_,  _expr_, _fact_,  _word_,  _num_};

Grammar lang_grammar(rule_list, nonterminals, terminals);