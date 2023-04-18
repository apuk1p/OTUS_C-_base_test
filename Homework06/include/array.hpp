#include "container.hpp"
#include <initializer_list>

template<typename T>
class Array : public Container<T>{
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
		Array(const int size);
		Array(const std::initializer_list<T> &rightVal);
		Array(const Array& other);
		Array(Array&& other) noexcept;
		~Array();

		void increase();
		void push_back(T value) override;
		int insert(int index, T value) override;
		int erase(int index) override;
		int reserve(int newsize);

		Iterator begin() {return Iterator(data);}
		Iterator end() {return Iterator(data + size_);}
		
		int size() const override;
		size_t capacity() const;
		
		T& operator[](const int & index );
		Array& operator=(const Array& right);
		Array& operator=(Array&& right) noexcept;

	private:
		T *data;
		int size_;
		size_t capacity_;
};