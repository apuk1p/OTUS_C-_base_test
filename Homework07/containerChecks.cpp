#pragma once

#include <iostream>
#include <string>
#include "include/array.hpp"
#include "include/list.hpp"

template<typename T>
T createContainer(T& name)
{
	name = {0,1,2,3,4,5,6,7,8,9};
	return name;
}

template<typename T, typename V>
T pushBackTest(T& name, V value)
{
	name.push_back(value);
	return name;
}

template<typename T, typename V>
T pushFrontTest(T& name, V value)
{
	name.push_front(value);
	return name;
}

template<typename T, typename V>
T pushMidTest(T& name, V value)
{
	name.insert( name.size()/2, value );
	return name;
}

template<typename T>
T erase(T& name, size_t index)
{
	name.erase( index );
	return name;
}

template<typename T>
std::string getValue(T& name, size_t index)
{
	size_t counter = 0;
	std::string value;
	for(const auto& val : name)
	{
		value = std::to_string(val);
		if(index == counter)
		{
			return value;
		}
		++counter;
	}
	return value;
}