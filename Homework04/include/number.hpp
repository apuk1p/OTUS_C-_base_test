#pragma once

#include <string>

#include "astnode.hpp"

class Number : public ASTNode {
	public:
		Number(int val) 
			: ASTNode(std::to_string(val)) 
			, val_(val) {}
		
		Number(const Number &other) = delete;

		Number &operator=(const Number &other) = delete;

		virtual ~Number() override;

	private:
		int val_;
};

Number::~Number ()
{
	// std::cout << this << std::endl;
	// std::cout << "Number destructor " << std::endl;
}
