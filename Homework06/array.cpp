#include "include/array.hpp"

template<typename T>
Array<T>::Array() : data(nullptr), size_(0), capacity_(0) {}

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
Array<T>::Array(const Array<T> &other) :
	data(new T[other.size_]),
	size_(other.size_),
	capacity_(other.capacity_)
{
	std::copy(other.data, other.data + size_, data);
	std::cout << "copy ctor" << std::endl;
}

template<typename T>
Array<T>::Array(Array&& other) noexcept : data(nullptr),size_(0),capacity_(0)
{
	std::swap(data, other.data);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
	std::cout << "move ctor" << std::endl;
}

template<typename T>
void Array<T>::increase()
{
	// std::cout << "create new memory" << std::endl;
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
void Array<T>::insert(int index, T value)
{
	if(index < 0 || index > capacity_)
	{
		throw std::invalid_argument("INDEX OUT OF RANGE");
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
}

template<typename T>
void Array<T>::erase(const int index)
{
	if(index < 0 || index > capacity_)
	{
		throw std::invalid_argument("INDEX OUT OF RANGE");
	}
	for(int i=index; i < size_; i++)
	{
		data[i] = data[i + 1];
	}
	size_--;
	//capacity_--; стоит ли уменьшать??
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

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& right)
{
	if(this != &right)
	{
		delete [] data;
		size_ = right.size_;
		data = new T[size_];
		std::copy(right.data, right.data + size_, data);
	}
	std::cout << "copy operator" << std::endl;
	return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept
{
	data = nullptr;
	size_ = 0;
	capacity_ = 0;
	if(this != &other)
	{
		std::swap(data, other.data);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
	}
	
	std::cout << "move operator" << std::endl;
	return *this;
}

template Array<int>;
template Array<double>;
// template Array<std::string>;