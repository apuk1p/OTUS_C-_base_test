#pragma once

#include <string>

#include "astnode.hpp"

class Mul : public ASTNode {
	public:
		Mul(std::string val, ASTNode *val1, ASTNode *val2) 
			: ASTNode(val,val1, val2) 
			, val_(val) {}
		
		Mul(const Mul &other) = delete;

		Mul &operator=(const Mul &other) = delete;

		~Mul() {delete &val_;};

		std::string val_;
};
