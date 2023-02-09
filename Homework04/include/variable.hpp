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

		virtual ~Variable() override;

	private:
		std::string val_;
};

Variable::~Variable ()
{
	//std::cout << this << std::endl;
	// std::cout << "Variable destructor " << std::endl;
}