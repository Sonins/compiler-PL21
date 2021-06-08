#include "Parser.hpp"

Parser::Parser() {
  extern Grammar lang_grammar;
  table = parsing_table(lang_grammar.get_rules_map());
}

Parser::~Parser() {
  
}

SyntaxTree* Parser::parse(std::list<Token> tokens) {

}

void Parser::print_parsing_table() {
  table.printout_table();
}
