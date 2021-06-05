#include <iostream>
#include <list>
#include <iostream>
#include <fstream>
#include "Scanner.hpp"
#include "Parser.hpp"
#include "CodeGenerator.hpp"

std::list<char> getSourceCode(char* sourceFileName) {
    std::ifstream inputFileStream(sourceFileName);

    if (inputFileStream.is_open()) {
        std::list<char> charList;
        char readedSourceChar;
        while ( inputFileStream.get(readedSourceChar) )
        {
            charList.push_back(readedSourceChar);
        }
        inputFileStream.close();

        return charList;
    } else {
        std::cout << "Fail to open the file";
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char* sourceFileName = argv[1];
        std::cout << sourceFileName << std::endl;

        std::list<char> sourceCode = getSourceCode(sourceFileName);

        /* For Debug */
        std::cout << "1. Get Source Code " << std::endl;
        for(std::list<char>::iterator iter = sourceCode.begin(); iter != sourceCode.end(); iter++){
            std::cout << *iter << "";
        }    
        std::cout << std::endl;

        std::list<Token> tokens = Scanner::scan(sourceCode);

        /* For Debug */
        std::cout << "2. Scanner " << std::endl;
        for(std::list<Token>::iterator iter = tokens.begin(); iter != tokens.end(); iter++){
            std::cout << iter->getType() << " ";
        }    
        std::cout << std::endl;

        SyntaxTree* syntaxTree = Parser::parse(tokens);

        // For Debug
        std::cout << "3. Parser " << std::endl;
        std::cout << std::endl;

        std::string targetCode = CodeGenerator::generate(syntaxTree);

        // For Debug
        std::cout << "4. Code Generator " << std::endl;
        std::cout << targetCode;
        std::cout << std::endl;
        
    } else {
        std::cout << "Please input the file name.";
    }
}
