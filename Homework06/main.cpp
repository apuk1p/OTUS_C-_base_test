#include "array.hpp"

template<typename T>
void print(Array<T> &arr)
{
	for(int i = 0; i < arr.size(); i++)
	{
		std::cout << "Value is: " << arr[i] << std::endl;
	}
	std::cout << '\n' << std::endl;
}

int main(){
	int size = 10;
	Array<int> ar1(size);
	Array<int> ar2{0,1,2,3,4,5,6,7,8,9};
	for(int i = 0; i < size; i++)
	{
		ar1.push_back(i);
		std::cout << "Value is: " << ar1[i] << std::endl;
	}
	std::cout << '\n' << std::endl;
	std::cout << "Array size is: " << ar1.size() << std::endl;

	ar1.erase(3);
	ar1.erase(5);
	ar1.erase(7);
	///////////////////////////////////////////////
	print(ar1);
	///////////////////////////////////////////////

	ar1.insert(0,10);
	print(ar1);
	///////////////////////////////////////////////
	
	ar1.insert(ar1.size()/2,20);
	print(ar1);
	///////////////////////////////////////////////
	ar1.insert(ar1.size(),30);
	print(ar1);
	


	return 0;
};