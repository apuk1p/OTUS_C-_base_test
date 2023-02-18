#include "../included/stdclass.hpp"
#include <cmath>

void StdClass::update(double next)
{
	sum_ += next;
	vect.push_back(next);

	if( sum_ > 0 && &vect != nullptr )
	{
		StdClass::calc();
	}
}

double StdClass::eval() const
{
	return m_std;
}

void StdClass::calc()
{
	double middle = 0;
	mean_ = sum_/vect.size();
	for (int i = 0; i < vect.size(); i ++)
	{
		middle += pow(vect[i] - mean_, 2);
	}
	m_std = sqrt(middle / vect.size() );
}