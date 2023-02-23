#include "../included/stdclass.hpp"
#include <cmath>
#include <iostream>

void StdClass::update(double next)
{
	vect.push_back(next);
	mean.update(next);
}

double StdClass::eval() const
{
	double middle = 0;
	for (int i = 0; i < vect.size(); i ++)
	{
		middle += pow(vect[i] - mean.eval(), 2);
	}
	return sqrt(middle / vect.size() );
}