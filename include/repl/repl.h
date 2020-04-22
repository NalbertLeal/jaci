#ifndef __repl_h__
#define __repl_h__

#include <iostream>

#include "token/token.h"
#include "lexer/lexer.h"

void startRepl(std::istream& in, std::ostream& out) {
    out << "Hello! This is the Nalbert programing language!\nFell free to type in commands\n";

    while(true) {
        std::string input = "";
        out << ">> ";
        std::getline(in, input);
        
        Lexer lexer(input);

        Token token;
        token.type = STARTING_LEXER;
        token.literal = "";

        while(token.type != FILE_EOF) {
            if(token.type == ILLEGAL) {
                out << "ERROR, illegal token: : " << token.literal << "\n";
                break;
            }
            if (token.type == BREAK_LINE) {
                token = lexer.nextToken();
                continue;
            }
            token = lexer.nextToken();
            out << token.type << " " << token.literal << "\n";
        }
    }
} 

#endif