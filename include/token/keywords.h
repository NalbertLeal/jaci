#ifndef __keywords_h__
#define __keywords_h__

#include <string>
#include <map>

#include "token_type.h"

std::map<std::string, TokenType> keywords = {
	{"if", IF},							// conditionals
	{"then", THEN},
	{"elif", ELIF},
	{"interface", INTERFACE},			// data abstractions
	{"trait", TRAIT},
	{"class", CLASS},
	{"actor", ACTOR},
	{"is", IS},							// blocks
	{"do", DO},
	{"end", END},
	{"func", FUNC},						 // procedures
	{"beh", BEH},
	{"return", RETURN},
	{"end", AND},						// logic
	{"or", OR},
	{"invariant", INVARIANT},			// formal verification
	{"ensure", ENSURE},
	{"require", REQUIRE},
	{"forall", FORALL},
	{"some", SOME},
	{"var", VAR},						// variables
	{"final", FINAL},
	{"const", CONST},
	{"in", IN},
	{"true", TRUE},						// booleans
	{"false", FALSE},
	{"int", INT}						// number types
};

TokenType lookupIdentifier(std::string identifier) {
	bool idExist = keywords.count(identifier) > 0;
	if(idExist) {
		return keywords[identifier];
	}
	return IDENT;
}

#endif
