#pragma once

#include <string>

#include "astnode.hpp"

class Mul : public ASTNode {
	public:
		Mul(std::string val, ASTNode *left, ASTNode *right) 
			: ASTNode(val, left, right) 
			, val_(val) {}
		
		Mul(const Mul &other) = delete;

		Mul &operator=(const Mul &other) = delete;

		virtual ~Mul() override;

	private:
		std::string val_;
};

Mul::~Mul ()
{
	// std::cout << this << std::endl;
	// std::cout << "Mul destructor " << std::endl;
}
