#pragma once

#include <string>

#include "astnode.hpp"

class Add : public ASTNode {
	public:
		Add(std::string val, ASTNode *val1, ASTNode *val2) 
			: ASTNode(val,val1, val2) 
			, val_(val) {}
		
		Add(const Add &other) = delete;

		Add &operator=(const Add &other) = delete;

		~Add() {delete &val_;};

		std::string val_;
};
