#pragma once

#include <string>

#include "astnode.hpp"

class Div : public ASTNode {
	public:
		Div(std::string val, ASTNode *left, ASTNode *right) 
			: ASTNode(val, left, right) 
			, val_(val) {}
		
		Div(const Div &other) = delete;

		Div &operator=(const Div &other) = delete;

		virtual ~Div() override;

	private:
		std::string val_;
};

Div::~Div ()
{
	// std::cout << this << std::endl;
	// std::cout << "Div destructor " << std::endl;
}
