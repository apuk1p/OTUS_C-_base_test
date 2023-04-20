#include "include/array.hpp"
#include "include/list.hpp"

template<typename T>
void print(List<T> &arr, std::string name)
{
	for(const auto& val : arr)
	{
		std::cout << name << " " << "value is: " << val << std::endl;
	}
	std::cout << '\n' << std::endl;
}

int main(){
	try
	{
		// int size = 10;
		// Array<int> ar1(size);
		// Array<int> ar2{0,1,2,3,4,5,6,7,8,9};
		// Array<int> ar3{3,2,1,0};
		// for(const auto& val : ar2)
		// {
		// 	ar1.push_back(val);
		// }
		// std::cout << '\n' << std::endl;
		// std::cout << "Array size is: " << ar1.size() << std::endl;

		// ar1.erase(3);
		// ar1.erase(5);
		// ar1.erase(7);
		// print(ar1);
		// ///////////////////////////////////////////////
		// ar1.insert(0,10);
		// print(ar1);
		// ///////////////////////////////////////////////
		// ar1.insert(ar1.size()/2,20);
		// print(ar1);
		// ///////////////////////////////////////////////
		// ar1.insert(ar1.size(),30);
		// print(ar1);
		// ar1 = ar3;
		// print(ar1);
		// Array<int> ar4(ar2);
		// print(ar4);
		// Array<int> ar5(std::move(ar3));
		// print(ar5);
		// print(ar3);
		// ar5 = std::move(ar4);
		// print(ar5);
		List<int> list{3,2,5,11,55,22};
		List<int>list2{1,1,1,1,1};
		List<int> list1{1,5,22};

		print(list1, "list 1");
		list1.insert(0,99);
		list1.insert(3, 33);
		list1.insert(10,66);
		// list1.insert(-5,100);
		print(list1, "list 1 after insert");
		std::cout << "check size: " << list1.size() << '\n' << std::endl;
		list1.erase(0);
		list1.erase(4);
		// list1.erase(6);
		print(list1, "list 1 after erase");
		std::cout << "check after move: " << list1.size() << '\n' << std::endl;

	}
	catch(const std::invalid_argument& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
	return 0;
};