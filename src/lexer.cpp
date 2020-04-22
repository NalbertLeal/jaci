#include <iostream>
#include <string>

#include "token/token.h"
#include "token/keywords.h"
#include "lexer/lexer.h"

Lexer::Lexer(std::string tInput) {
	mInput = tInput;
	if(mInput[mInput.size()-1] != '\0') {
		mInput += std::string(1, '\0');
	}

	readChar();
}

void Lexer::readChar() {
	if(mReadPosition >= mInput.size()) {
		mCurrent = '\0';
	} else {
		mCurrent = mInput[mReadPosition];
	}
	mPosition = mReadPosition;
	mReadPosition++;
}

Token Lexer::nextToken() { 
	Token token;

	skipWhitespace();

	switch(mCurrent) {
		case ':':
			if(peekChar() == '=') {
				token.type = ASSIGN;
				readChar();
				token.literal = ":=";
			} else {
				token.type = ILLEGAL;
				token.literal = mCurrent;
			}
			break;
		case '(':
			token.type = LPAREN;
			token.literal = '(';
			break;
		case ')':
			token.type = RPAREN;
			token.literal = ')';
			break;
		case '{':
			token.type = LBRACE;
			token.literal = '{';
			break;
		case '}':
			token.type = RBRACE;
			token.literal = '}';
			break;
		case '=':
			token.type = EQUAL;
			token.literal = '=';
			break;
		case '+':
			if(peekChar() == '+') {
				token.type = UPLUS;
				readChar();
				token.literal = "++";
			} else {
				token.type = PLUS;
				token.literal = "+";
			}
			break;
		case '-':
			if(peekChar() == '-') {
				if(peek2Char() == '>') {
					token.type = CONDITIONAL;
					readChar();
					readChar();
					token.literal = "-->";
				} else {
					token.type = UMINUS;
					readChar();
					token.literal = "--";
				}
			} else {
				token.type = MINUS;
				token.literal = "-";
			}
			break;
		case '*':
			token.type = ASTERISK;
			token.literal = "*";
			break;
		case '/':
			if(peekChar() == '=') {
				token.type = NOT_EQUAL;
				readChar();
				token.literal = "/=";
			} else {
				token.type = SLASH;
				token.literal = "/";
			}
			break;
		case ';':
			token.type = SEMICOLLON;
			token.literal = ';';
			break;
		case ',':
			token.type = COMMA;
			token.literal = ',';
			break;
		case '<':
			if(peekChar() == '=') {
				token.type = EQUAL_LESS_THAN;
				readChar();
				token.literal = "<=";
			} else {
				token.type = LESS_THAN;
				token.literal = "<";
			}
			break;
		case '>':
			if(peekChar() == '=') {
				token.type = EQUAL_GREATER_THAN;
				readChar();
				token.literal = ">=";
			} else {
				token.type = GREATER_THAN;
				token.literal = ">";
			}
			break;
		case '~':
			token.type = TIL;
			token.literal = "~";
			break;
		case '&':
			token.type = FINANCE_E;
			token.literal = "&";
			break;
		case '|':
			token.type = VERTICAL_BAR;
			token.literal = "|";
			break;
		case '\n':
			token.type = BREAK_LINE;
			token.literal = '\n';
			break;
		case '\0':
			token.type = FILE_EOF;
			token.literal = '\0';
			return token;
		default:
			if(isLetter()) {
				token.literal = readIdentifier();
				token.type = lookupIdentifier(token.literal);
				return token; 
			} else if(isDigit()) {
				token.type = INT;
				token.literal = readNumber();
				return token; 
			} else {
				token.type = ILLEGAL;
				token.literal = std::string(1, mCurrent);
				// return token; 
			}
	}

	readChar();
	return token;
}

// helpers

std::string Lexer::readIdentifier() {
	std::string identifier = "";
	while(isLetter()) {
		identifier += std::string(1, mCurrent);
		readChar();
	}
	return identifier;
}

bool Lexer::isLetter() {
	int ascii = int(mCurrent);
	return (int('a') <= ascii and ascii <= int('z')) or (int('A') <= ascii and ascii <= int('z')) or ascii == int('_');
}

void Lexer::skipWhitespace() {
	// int ascii = int(mCurrent);
	// test if mCurrent is ' ' or \n or \t
	// while(ascii == 32 || ascii == 9 || ascii == 13) {
	while(mCurrent == ' ' or mCurrent == '\t' or mCurrent == '\r') {
		readChar();
		// ascii = int(mCurrent);
	}
}

std::string Lexer::readNumber() {
	std::string number = "";
	while(isDigit()) {
		number += std::string(1, mCurrent);
		readChar();
	}
	return number;
}

bool Lexer::isDigit() {
	int ascii = int(mCurrent);
	return int('0') <= ascii and ascii <= int('9');
}

char Lexer::peekChar() {
	if(mReadPosition >= mInput.size()) {
		return '\0';
	} else {
		return mInput[mReadPosition];
	}
}

char Lexer::peek2Char() {
	if(mReadPosition+1 >= mInput.size()) {
		return '\0';
	} else {
		return mInput[mReadPosition+1];
	}
}