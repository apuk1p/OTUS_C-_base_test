#include "include/list.hpp"

template<typename T>
List<T>::List()
{
	this->head = new Node{nullptr, 0, nullptr};
}

template<typename T>
List<T>::List(const std::initializer_list<T>& newvalue) : size_(0)
{
	for(const auto& val : newvalue)
	{
		Node* mNode = new Node(tail, val, nullptr);
		if(head == nullptr)
		{
			head = mNode;
		}
		if(size_ > 0)
		{
			tail->next_ = mNode;
		}
		tail = mNode;
		size_++;
	}
}


template<typename T>
List<T>::List(const List<T>& other)
{
	this->head = new Node{nullptr, other.head->value, nullptr};

	Node* otherNode = other.head;
	Node* thisNode = this->head;
	this->size_ = other.size_;

	while(otherNode->next_)
	{
		otherNode = otherNode->next_;
		Node* newnode = new Node{thisNode, otherNode->value, nullptr};
		thisNode->next_ = newnode;
		thisNode = thisNode->next_;
	}
	this->tail = thisNode;
}

template<typename T>
List<T>::List(List<T>&& other) noexcept
{
	this->head = new Node{nullptr, 0, nullptr};
	this->tail = this->head;
	this->size_ = other.size_;
	other.size_ = 0;

	std::swap(this->head, other.head);
	std::swap(this->tail, other.tail);
}

template<typename T>
List<T>::~List()
{
	Node* currentNode = this->head;
	while (currentNode)
	{
		Node* nextNode = currentNode->next_;
		delete currentNode;
		currentNode = nextNode;
	}
	std::cout << "Destructor list called" << std::endl;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if(this != &other)
	{
		Node* currentNode = this->head;
		Node* otherNode = other.head;
		Node* tempNode = this->head;
		this->size_ = other.size_;
		while(otherNode)
		{
			currentNode->value = otherNode->value;
			if(!currentNode->next_ && otherNode->next_)
			{
				Node* newNode = new Node{otherNode, otherNode->value, nullptr};
				currentNode->next_ = newNode;
				this->tail = newNode;
			}
			tempNode = currentNode;
			currentNode = currentNode->next_;
			otherNode = otherNode->next_;

			
			if(!otherNode && currentNode)
			{
				tempNode->next_ = nullptr;
				this->tail = tempNode;

				while(currentNode)
				{
					Node* nextNode = currentNode->next_;
					delete currentNode;
					currentNode = nextNode;
				}
			}
		}
	}
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& other) noexcept
{
	if(this != & other)
	{
		Node* temp = this->head;
		while(temp->next_)
		{
			Node* nextTemp = temp->next_;
			temp->next_ = nullptr;
			temp->prev_ = nullptr;
			temp->value = 0;
			temp = nextTemp;
		}
		this->tail = temp;
		this->size_ = other.size_;
		other.size_ = 0;

		std::swap(this->head, other.head);
		std::swap(this->tail, other.tail);
	}
	
	return *this;
}

template<typename T>
void List<T>::push_back(T value)
{
	Node* curNode = this->head;
	if(!curNode)
	{
		Node* newNode = new Node{nullptr,value,nullptr};
		head = newNode;
		tail = newNode;
		size_ = 1;
	}
	else
	{
		Node* new_node = new Node{tail,value,nullptr};
		tail->next_ = new_node;
		tail = tail->next_;
		size_++;
	}

}

template<typename T>
void List<T>::insert(int index, T value)
{
	if(index < 0 )
	{
		throw std::invalid_argument("NEGATIVE INDEX");
	}
	if(index == 0)
	{
		Node* curNode = this->head;
		Node* newNode = new Node{nullptr, value, curNode};
		curNode->prev_ = newNode;
		this->head = newNode;
		++size_;
	}
	else
	{
		int counter = 1;
		Node* curNode = this->head;
		while(counter != index && curNode->next_)
		{
			curNode = curNode->next_;
			++counter;
		}
		Node* newNodeSec = new Node{curNode, value, curNode->next_};
		if(!curNode->next_)
		{
			newNodeSec->next_ = nullptr;
			curNode->next_ = newNodeSec;
			this->tail = newNodeSec;
			++size_;
			std::cout << "Index out of range, it was added to " <<
						"the end of the container. It's index is " << size_ << std::endl;
		}
		else{
			Node* nextNode = curNode;
			curNode = curNode->next_;
			nextNode->next_ = newNodeSec;
			curNode->prev_ = newNodeSec;
			++size_;
		}
	}
}

template<typename T>
void List<T>::erase(int index)
{
	if(index < 0 || index > size_)
	{
		throw std::invalid_argument("INDEX OUT OF RANGE");
	}
	if(index == 0)
	{
		Node* nextNode = this->head->next_;
		nextNode->prev_ = nullptr;
		delete this->head;
		this->head = nextNode;
		--size_;
	}
	else
	{
		int counter = 1;
		Node* curNode = this->head;
		while(counter != index)
		{
			curNode = curNode->next_;
			++counter;
		}
		Node* prevNode = curNode->prev_;
		if(!curNode->next_)
		{
			prevNode->next_ = nullptr;
			this->tail = prevNode;
			delete curNode;
			--size_;
		}
		else
		{
			Node* nextNode = curNode->next_;
			prevNode->next_ = nextNode;
			nextNode->prev_ = prevNode;
			delete curNode;
			--size_;
		}
	}
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
	node_ = node_ -> next_;
	return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
	Iterator i = *this;
	node_ = node_ -> next_;
	return i;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--()
{
	node_ = node_ -> next_;
	return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
	Iterator i = *this;
	node_ = node_ -> prev_;
	return i;
}

template List<int>;
template List<double>;
// template Array<std::string>;