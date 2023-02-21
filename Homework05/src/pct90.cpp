#include "../included/pct90.hpp"
#include <algorithm>
#include <iostream>

void Pct90::update(double next)
{
	vect.push_back(next);
}

double Pct90::eval() const
{
	double pct90 = 0;
	pct90 = 0.9 * (vect.size());
	
	std::sort(vect.begin(), vect.end());

	for (int i = 0; i < vect.size(); i ++)
	{
		if((int)pct90 == i)
		{
			pct90 = vect[i];
			break;
		}
	}

	return pct90;
}