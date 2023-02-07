#pragma once

#include <string>

#include "astnode.hpp"

class Sub : public ASTNode {
	public:
		Sub(std::string val, ASTNode *val1, ASTNode *val2) 
			: ASTNode(val,val1, val2) 
			, val_(val) {}
		
		Sub(const Sub &other) = delete;

		Sub &operator=(const Sub &other) = delete;

		~Sub() {delete &val_;};

		std::string val_;
};
