#pragma once

#include <string>

#include "astnode.hpp"

class Variable : public ASTNode {
	public:
		Variable(std::string val) 
			: ASTNode(val) 
			, val_(val) {}
		
		Variable(const Variable &other) = delete;

		Variable &operator=(const Variable &other) = delete;

		~Variable() {delete &val_;};

		std::string val_;
};
