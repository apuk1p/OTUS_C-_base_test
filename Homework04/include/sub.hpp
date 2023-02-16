#pragma once

#include <string>

#include "astnode.hpp"

class Sub : public ASTNode {
	public:
		Sub(std::string val, ASTNode *left, ASTNode *right) 
			: ASTNode(val, left, right) 
			, val_(val) {}
		
		Sub(const Sub &other) = delete;

		Sub &operator=(const Sub &other) = delete;

		virtual ~Sub() override;

	private:
		std::string val_;
};

Sub::~Sub ()
{
	// std::cout << this << std::endl;
	// std::cout << "Sub destructor " << std::endl;
}