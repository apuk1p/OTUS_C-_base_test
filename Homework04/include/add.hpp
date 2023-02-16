#pragma once

#include <string>

#include "astnode.hpp"

class Add : public ASTNode {
	public:
		Add(std::string val, ASTNode *left, ASTNode *right) 
			: ASTNode(val, left, right) 
			, val_(val) 
			{
				// std::cout << this << std::endl;
				// std::cout << "this Add" << std::endl;
			}
		
		Add(const Add &other) = delete;

		Add &operator=(const Add &other)  = delete;

		virtual ~Add() override;

	private:
		std::string val_;
};

Add::~Add ()
{
	// std::cout << this << std::endl;
	// std::cout << "Add destructor " << std::endl;
}