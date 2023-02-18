#include "../included/stdclass.hpp"
#include <cmath>
#include <iostream>

void StdClass::update(double next)
{
	sum_ += next;
	vect.push_back(next);
}

double StdClass::eval() const
{
	return m_std;
}

void StdClass::calc()
{
	mean_ = sum_/vect.size();
	for (int i = 0; i < vect.size(); i ++)
	{
		m_std += pow(vect[i] - mean_, 2);
	}
	m_std = sqrt(m_std / ( vect.size() - 1 ) );
}