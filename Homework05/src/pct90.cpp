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
	
	std::vector<double> vectSorted = vect;
	std::sort(vectSorted.begin(), vectSorted.end());

	for (int i = 0; i < vectSorted.size(); i ++)
	{
		if((int)pct90 == i)
		{
			pct90 = vectSorted[i];
			break;
		}
	}

	return pct90;
}