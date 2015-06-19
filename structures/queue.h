#ifndef H_queue
#define H_queue

#include <iostream>
#include <exception>
#include <stdexcept>

template <class Type>
class Cvor
{
	private:
		Type info;
		Cvor* link;
	public:
		Cvor() = default;
		Cvor(const Type& i, Cvor * l = nullptr) : info(i), link(l) {};
		Type& getInfo() {return info;}
		Cvor* getLink() {return link;}
		void setInfo(Type T) {info=T;}
		void setLink(Cvor* L) {link=L;}
};

template <class Type>
class queue
{
private:
	Cvor<Type> *head;
	Cvor<Type> *tail; 
	int _size;
	void copyQueue(const queue<Type>& otherQueue); 
public:
	const queue<Type>& operator=(const queue<Type>&);
	int size() const;
	bool empty() const;	
	void initializeQueue();
	const Type& front() const;
	const Type& back() const;
    Type& front();
	Type& back();
	void push(const Type& queueElement);
	void pop();
	queue();
	queue(const queue<Type>& otherQueue);
	~queue(); 
	
	friend ostream& operator<<(ostream & izlaz, const queue<Type>& otherQueue){
	
	        Cvor<Type>  *current;	
	
	    	current = otherQueue.head; 	

	        while (current != nullptr)		
	        {
		        izlaz<<current->getInfo()<<"\t"; 
		        current = current->getLink(); 
	        }
	
	        return izlaz;
	}
};

template <class Type>
int queue<Type>::size() const {
    return _size;
}

template <class Type>
bool queue<Type>::empty() const {
    return(_size == 0);
}

template <class Type>
queue<Type>::~queue(){
	initializeQueue();
}


template <class Type>
void queue<Type>::copyQueue(const queue<Type>& otherQueue)
{
	Cvor<Type>  *current;			
	if (head != nullptr) 			
		initializeQueue();

		
	current = otherQueue.head; 

	while (current != nullptr)		
	{
		push(current->getInfo()); 
		current = current->getLink(); 
	}
	
} 

template <class Type>
queue<Type>::queue(const queue<Type>& otherQueue)
{
	head = nullptr;	
	tail  = nullptr;      
	copyQueue(otherQueue);	
}

template <class Type>
const queue<Type>& queue<Type>::operator=(const queue<Type>& otherQueue)
{
	if (this != &otherQueue) 	
		copyQueue(otherQueue);	
	return *this;
}


template <class Type>
void queue<Type>::initializeQueue()
{
	Cvor<Type> *temp;
	while (head!= nullptr)
	{
		temp = head; 
		head = head->getLink(); 
		delete temp;
	}
	tail = nullptr;
} 

template <class Type>
void queue<Type>::push(const Type& newElement)
{
	Cvor<Type> *newNode;
	newNode = new Cvor<Type>(newElement);
	
	if (empty()) 
	{
		head = newNode;		
	}
	else
	{
		tail->setLink(newNode);		
	}
	tail = newNode;
	_size++;
}

template <class Type>
const Type& queue<Type>::front() const
{
	if(head == nullptr) throw std::underflow_error("Red prazan");
	return head->getInfo();
} 

template <class Type>
const Type& queue<Type>::back() const
{
	if(head == nullptr) throw std::underflow_error("Red prazan");
	return tail->getInfo();
}

template <class Type>
Type& queue<Type>::front() 
{
	if(head == nullptr) throw std::underflow_error("Red prazan");
	return head->getInfo(); 
} 

template <class Type>
Type& queue<Type>::back() 
{
	if(head == nullptr) throw std::underflow_error("Red prazan");
	return tail->getInfo();
}

template <class Type>
void queue<Type>::pop()
{
	Cvor<Type> *temp;
	if (!empty())
	{
		temp = head;
		head = head->getLink();
		delete temp;
		if (head == nullptr) 
			tail = nullptr; 
		_size--;
	}
	
}
template<class Type>
queue<Type>::queue()
{
	head = nullptr; 
	tail = nullptr;
	_size = 0; 
} 

#endif
