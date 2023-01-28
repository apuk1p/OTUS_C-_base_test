#include <iostream>
#include <string>

int levels(const int &level){
	int max_value = 0;
	switch (level)
	{
	case 1:
		max_value = 10;
		break;
	case 2:
		max_value = 50;
		break;
	case 3:
		max_value = 100;
		break;
	
	default:
		max_value = 50;
		break;
	}
	return max_value;
}