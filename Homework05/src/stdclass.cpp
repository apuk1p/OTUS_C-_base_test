#include "../included/stdclass.hpp"

void StdClass::update(double next)
{
	mean_ += next;
	vect.push_back(next);
}

double StdClass::eval() const
{
	const_cast<StdClass*>( this )->calc();
	return m_std;
}

void StdClass::calc()
{
	mean_ /= vect.size() - 1;
	for (int i = 0; i < vect.size() - 1; i ++)
	{
		m_std += pow(vect[i] - mean_, 2);
	}
	m_std = sqrt(m_std / ( vect.size() - 1 ) );
}