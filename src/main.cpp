#include <cstdio>
#include <iostream>

#include "token/token.h"
#include "lexer/lexer.h"
#include "repl/repl.h"

int main() {
	startRepl(std::cin, std::cout);

	return EXIT_SUCCESS;
}
