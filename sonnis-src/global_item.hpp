#include <vector>

#include "grammar.hpp"
#include "item.hpp"

using std::vector;

item _prog_("#prog", item_type::nonterminal);
item _decls_("#decls", item_type::nonterminal);
item _decl_("#decl", item_type::nonterminal);
item _vtype_("#vtype", item_type::nonterminal);
item _block_("#block", item_type::nonterminal);
item _slist_("#slist", item_type::nonterminal);
item _stat_("#stat", item_type::nonterminal);
item _cond_("#cond", item_type::nonterminal);
item _expr_("#expr", item_type::nonterminal);
item _fact_("#fact", item_type::nonterminal);
item _word_("#word", item_type::nonterminal);
item _num_("#num", item_type::nonterminal);

item _propen_("(", item_type::terminal);
item _prclose_(")", item_type::terminal);
item _brk_(";", item_type::terminal);
item _bopen_("{", item_type::terminal);
item _bclose_("}", item_type::terminal);
item _intdecl_("int", item_type::terminal);
item _chardecl_("char", item_type::terminal);
item _if_("IF", item_type::terminal);
item _then_("THEN", item_type::terminal);
item _else_("ELSE", item_type::terminal);
item _eq_("=", item_type::terminal);
item _exit_("EXIT", item_type::terminal);
item _lgreater_(">", item_type::terminal);
item _plus_("+", item_type::terminal);
regex_item _word_term_("([a-z]|[A-Z])*", item_type::terminal);
regex_item _num_term_("[0-9]*", item_type::terminal);

item _empty_("000", item_type::terminal);
item _EOF_("$", item_type::terminal);

// empty result should be first!
vector<rule> rule_list = {
    rule(_decls_, vector<item>{_empty_}),
    rule(_vtype_, vector<item>{_empty_}),
    rule(_block_, vector<item>{_empty_}),
    rule(_stat_, vector<item>{_empty_}),
    rule(_prog_, vector<item>{_word_, _propen_, _prclose_, _block_}),
    rule(_decls_, vector<item>{_decls_, _decl_}),
    rule(_decl_, vector<item>{_vtype_, _word_, _brk_}),
    rule(_vtype_, vector<item>{_intdecl_}),
    rule(_vtype_, vector<item>{_chardecl_}),
    rule(_block_, vector<item>{_bopen_, _decls_, _slist_, _bclose_}),
    rule(_slist_, vector<item>{_slist_, _stat_}),
    rule(_slist_, vector<item>{_stat_}),
    rule(_stat_, vector<item>{_if_, _cond_, _then_, _else_, _block_}),
    rule(_stat_, vector<item>{_word_, _eq_, _expr_, _brk_}),
    rule(_stat_, vector<item>{_exit_, _expr_, _brk_}),
    rule(_cond_, vector<item>{_expr_, _lgreater_, _expr_}),
    rule(_expr_, vector<item>{_expr_, _plus_, _fact_}),
    rule(_expr_, vector<item>{_fact_}),
    rule(_fact_, vector<item>{_num_}),
    rule(_fact_, vector<item>{_word_}),
    rule(_word_, vector<item>{_word_term_}),
    rule(_num_, vector<item>{_num_term_})};

vector<item> terminals = {_propen_,   _prclose_, _brk_,       _bopen_,
                          _bclose_,   _intdecl_, _chardecl_,  _if_,
                          _then_,     _else_,    _eq_,        _exit_,
                          _lgreater_, _plus_,    _word_term_, _num_term_};

vector<item> nonterminals = {_prog_, _decls_, _decl_, _vtype_, _block_, _slist_,
                             _stat_, _cond_,  _expr_, _fact_,  _word_,  _num_};

grammar lang_grammar(rule_list, nonterminals, terminals);