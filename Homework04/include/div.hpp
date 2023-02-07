#pragma once

#include <string>
#include <iostream>
#include <cctype>

#include "astnode.hpp"

class Div : public ASTNode {
	public:
		Div(std::string val, ASTNode *val1, ASTNode *val2) 
			: ASTNode(val,val1, val2) 
			, val_(val) {}
		
		Div(const Div &other) = delete;

		Div &operator=(const Div &other) = delete;

		~Div() {delete &val_;};

		std::string val_;
};
