#ifndef __lexer_h__
#define __lexer_h__

#include <string>

#include "token/token.h"

class Lexer {
	public:
		std::string mInput;
		unsigned int mPosition = 0;
		unsigned int mReadPosition = 0;
		char mCurrent;

		Lexer(std::string tInput);

		void readChar();
		Token nextToken();
		
		// helpers
		bool isLetter();
		std::string readIdentifier();
		void skipWhitespace();
		bool isDigit();
		std::string readNumber();
		char peekChar();
		char peek2Char();

};

#include "../src/lexer.cpp"

#endif
