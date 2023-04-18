#include "container.hpp"
#include <initializer_list>

template<typename T>
class List : public Container<T>{
	public:
		struct Node{
			Node(Node *prev, T val, Node *next) 
			: prev_(prev),
			value(val),
			next_(next) {}
			
			T value;
			Node *next_;
			Node * prev_;
		};

		class Iterator
		{
			public:
				Iterator(Node* mNode) : node_(mNode) {}
				Iterator& operator++();
				Iterator operator++(int);
				T& operator*() {return node_->value;}
				// T operator*() {return node_->value;}
				T* operator->() {return &node_->value;}
				bool operator==(Iterator &right) {return node_==right.node_;}
				bool operator!=(Iterator &right) {return node_!=right.node_;}
			private:
				Node* node_ = nullptr;
		};
		List();
		List(const std::initializer_list<T>& newData);
		~List();
		List(const List& other);
		List(List&& other) noexcept;
		List& operator=(const List& other);
		List& operator=(List&& other) noexcept;

		void push_back(T value) override;
		int insert(int index, T value) override;
		int erase(int index) override;
		int size() const {return size_;}

		Iterator begin() {return Iterator(head);}
		Iterator end() {return Iterator(tail->next_);}

	private:
		Node *head = nullptr;
		Node *tail = nullptr;
		int size_; 

};