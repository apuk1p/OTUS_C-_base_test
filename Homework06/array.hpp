#include "container.hpp"
#include <initializer_list>

template<typename T>
class Array : public Container<T>{
	public:
		Array(const int size);
		Array(const std::initializer_list<T> &rightVal);
		~Array();

		void increase();
		void push_back(T value) override;
		int insert(int index, T value) override;
		int erase(int index) override;
		int reserve(int newsize);
		
		int size() const override;
		size_t capacity() const;
		
		T& operator[](const int & index ) override;

	private:
		T *data;
		int size_;
		size_t capacity_;
};