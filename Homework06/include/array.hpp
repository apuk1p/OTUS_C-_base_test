#pragma once 
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template<typename T>
class Array{
	public:
		class Iterator
		{
			public:
				Iterator(T *ptr): ptr_(ptr) {}
				Iterator operator++() {ptr_++; return *this;}
				Iterator operator++(int) {Iterator i = *this; ++*this; return i;}
				Iterator operator--() {ptr_--; return *this;}
				Iterator operator--(int) {Iterator i = *this; --*this; return i;}
				T& operator*() {return *ptr_;}
				T* operator->() {return ptr_;}
				bool operator== (const Iterator& val) {return ptr_==val.ptr_;}
				bool operator!= (const Iterator& val) {return ptr_!=val.ptr_;}
			private:
				T *ptr_;
		};
		Array();
		Array(const size_t size);
		Array(const std::initializer_list<T> &rightVal);
		Array(const Array& other);
		Array(Array&& other) noexcept;
		~Array();

		void increase();
		void push_back(T value);
		void insert(size_t index, T value);
		void erase(size_t index);
		void reserve(size_t newsize);

		Iterator begin() {return Iterator(data);}
		Iterator end() {return Iterator(data + size_);}
		
		size_t size() const;
		size_t capacity() const;
		
		T& operator[](const size_t & index );
		Array& operator=(const Array& right);
		Array& operator=(Array&& right) noexcept;

	private:
		T *data;
		size_t size_;
		size_t capacity_;
};


template<typename T>
Array<T>::Array() : data(nullptr), size_(0), capacity_(0) {}

template<typename T>
Array<T>::Array(const size_t size) : size_(0), capacity_(size)
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
	for(size_t i = 0; i < size_; i++)
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
void Array<T>::insert(size_t index, T value)
{
	if(index > capacity_)
	{
		throw std::invalid_argument("INDEX OUT OF RANGE");
	}
	if (size_ >= capacity_)
	{
		increase();
	}
	for (size_t i = size_ - 1; i >= index; i --)
	{
		data[i + 1] = data[i];
	}
	data[index] = value;
	size_++;
}

template<typename T>
void Array<T>::erase(size_t index)
{
	if(index + 1 > size_)
	{
		throw std::invalid_argument("INDEX OUT OF RANGE");
	}
	for(size_t i=index + 1; i < size_; i++)
	{
		data[i - 1] = data[i];
	}
	size_--;
}

template<typename T>
void Array<T>::reserve(size_t newsize)
{
	if(newsize < size_)
	{
		throw std::invalid_argument("New capacity lower then current size");
	}
	capacity_ = newsize;
	increase();
}

template<typename T>
size_t Array<T>::size() const
{
	return size_;
}

template<typename T>
size_t Array<T>::capacity() const
{
	return capacity_;
}

template<typename T>
T& Array<T>::operator[](const size_t & index)
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
	if(this != &other)
	{
		data = nullptr;
		size_ = 0;
		capacity_ = 0;
		std::swap(data, other.data);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
	}
	
	std::cout << "move operator" << std::endl;
	return *this;
}
