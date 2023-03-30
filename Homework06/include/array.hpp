#include "container.hpp"
#include <initializer_list>

template<typename T>
class Array : public Container<T>{
	public:
		class iterator
		{
			public:
				iterator(T *ptr): ptr_(ptr) {}
				iterator operator++() {ptr_++; return *this;}
				iterator operator++(int) {iterator i = *this; ++*this; return i;}
				iterator operator--() {ptr_--; return *this;}
				iterator operator--(int) {iterator i = *this; --*this; return i;}
				T& operator&() {return *ptr_;}
				T* operator*() {return ptr_;}
				bool operator== (const iterator& val) {return ptr_==val.ptr_;}
				bool operator!= (const iterator& val) {return ptr_!=val.ptr_;}
			private:
				T *ptr_;
		};
		Array();
		Array(const int size);
		Array(const std::initializer_list<T> &rightVal);
		~Array();
		Array(const Array& other);
		Array(Array&& other) noexcept;

		void increase();
		void push_back(T value) override;
		int insert(int index, T value) override;
		int erase(int index) override;
		int reserve(int newsize);

		iterator begin() {return iterator(data);}
		iterator end() {return iterator(data + size_);}
		
		int size() const override;
		size_t capacity() const;
		
		T& operator[](const int & index ) override;
		Array& operator=(const Array& right);
		Array& operator=(Array&& right) noexcept;

	private:
		T *data;
		int size_;
		size_t capacity_;
};