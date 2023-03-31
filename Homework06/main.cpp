#include "include/array.hpp"

template<typename T>
void print(Array<T> &arr)
{
	for(const auto& val : arr)
	{
		std::cout << "value is: " << val << std::endl;
	}
	std::cout << '\n' << std::endl;
}

int main(){
	int size = 10;
	Array<int> ar1(size);
	Array<int> ar2{0,1,2,3,4,5,6,7,8,9};
	Array<int> ar3{3,2,1,0};
	for(const auto& val : ar2)
	{
		ar1.push_back(val);
	}
	std::cout << '\n' << std::endl;
	std::cout << "Array size is: " << ar1.size() << std::endl;

	ar1.erase(3);
	ar1.erase(5);
	ar1.erase(7);
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
	ar1 = ar3;
	print(ar1);
	Array<int> ar4(ar2);
	print(ar4);
	Array<int> ar5(std::move(ar3));
	print(ar5);
	print(ar3);
	ar5 = std::move(ar4);
	print(ar5);

	return 0;
};