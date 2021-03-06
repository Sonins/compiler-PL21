#include "Parser.hpp"

Parser::Parser() {
  extern Grammar lang_grammar;
  table = new parsing_table(lang_grammar.get_rules_map());
}

Parser::~Parser() {
  delete table;
}

SyntaxTree* Parser::parse(std::list<Token> tokens) {

}

void Parser::print_parsing_table() {
  table->printout_table();
}
