#ifndef __tokens_h__
#define __tokens_h__

#include "string"

#include "token_type.h"

class Token {
	public:
		TokenType type;
		std::string literal;
};

#endif
