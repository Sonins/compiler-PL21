#include <iostream>
#include <list>
#include "Scanner.hpp"
#include "Parser.hpp"
#include "CodeGenerator.hpp"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char* sourceFileName = argv[1];

        std::string sourceCode = "source code";

        std::list<Token*> tokens = Scanner::scan(sourceCode);

        SyntaxTree* syntaxTree = Parser::parse(tokens);

        std::string code = CodeGenerator::generate(syntaxTree);

    } else {
        std::cout << "Please input the file name.";
    }
}
