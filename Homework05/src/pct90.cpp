#include "../included/pct90.hpp"
#include <algorithm>

void Pct90::update(double next)
{
	vect.push_back(next);
	
	Pct90::calc();
}

double Pct90::eval() const
{
	return m_pct90;
}

void Pct90::calc()
{
	double pct90 = 0;
	pct90 = 0.9 * (vect.size());
	std::sort(vect.begin(), vect.end());
	
	for (int i = 0; i < vect.size(); i ++)
	{
		if((int)pct90 == i)
		{
			m_pct90 = vect[i];
		}
	}
}