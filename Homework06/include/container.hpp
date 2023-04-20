#pragma once 
#include <iostream>
#include <stdexcept>

template<typename T>
class Container{
	public:
		virtual void push_back(T value) = 0;
		virtual void insert(int index, T value) = 0;
		virtual void erase(int index) = 0;
		virtual int size() const = 0;
};