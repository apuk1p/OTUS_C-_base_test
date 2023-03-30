#pragma once 
#include <iostream>

template<typename T>
class Container{
	public:
		virtual void push_back(T value) = 0;
		virtual int insert(int index, T value) = 0;
		virtual int erase(int index) = 0;
		virtual int size() const = 0;
		virtual T& operator[](const int& index) = 0;

};