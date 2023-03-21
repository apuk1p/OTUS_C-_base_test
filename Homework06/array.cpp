#include "array.hpp"

template<typename T>
Array<T>::Array(const int size) : size_(0), capacity_(size)
{
	data = new T[capacity_];
}


template<typename T>
Array<T>::Array(const std::initializer_list<T> &rightVal) : size_(0), capacity_(0)
{
	data = new T[rightVal.size()];
	capacity_ = rightVal.size();
	for(const auto& value : rightVal)
	{
		data[size_] = value;
		size_++;
	}
}

template<typename T>
Array<T>::~Array()
{
	delete [] data;
}

template<typename T>
void Array<T>::increase()
{
	std::cout << "create new memory" << std::endl;
	T* new_order = new T[capacity_+1];
	for(int i = 0; i < size_; i++)
	{
		new_order[i] = data[i];
	}
	delete [] data;
	data = new_order;
	capacity_++;
}

template<typename T>
void Array<T>::push_back(T value)
{
	if(size_ >= capacity_)
	{
		increase();
	}
	// std::cout << "use capacity" << std::endl;
	data[size_] = value;
	size_++;
}

template<typename T>
int Array<T>::insert(int index, T value)
{
	if(index < 0 || index > capacity_)
	{
		std::cout << "Index out of range" << std::endl;
		return -1;
	}
	if (size_ >= capacity_)
	{
		increase();
	}
	for (int i = size_ - 1; i >= index; i --)
	{
		data[i + 1] = data[i];
	}
	data[index] = value;
	size_++;
	return 0;
}

template<typename T>
int Array<T>::erase(const int index)
{
	if(index < 0 || index > capacity_)
	{
		std::cout << "Index out of range" << std::endl;
		return -1;
	}
	for(int i=index; i < size_; i++)
	{
		data[i] = data[i + 1];
	}
	size_--;
	//capacity_--; стоит ли уменьшать??
	return 0;
}

template<typename T>
int Array<T>::reserve(const int newsize)
{
	if (newsize < capacity_)
	{
		std::cout << "The new size is lower then current size!" << std::endl;
		return -1;
	}
	capacity_ = newsize;
	increase();
	return 0;
}

template<typename T>
int Array<T>::size() const
{
	return size_;
}

template<typename T>
size_t Array<T>::capacity() const
{
	return capacity_;
}

template<typename T>
T& Array<T>::operator[](const int & index)
{
	return data[index];
}

template Array<int>;
template Array<double>;
template Array<std::string>;