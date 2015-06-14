#ifndef _LISTA2_HXX
#define _LISTA2_HXX
#include <iostream>
#include <string>

using namespace std;

template<typename Type>
class Node
{
	private:
		Type info;
		Node* next;
		Node* prev;
		
	public:
		void setInfo( const Type& newinfo ){ info=newinfo; }
		void setPrev( Node* newprev ){ prev = newprev; }
		void setNext( Node* newnext ){ next = newnext; }
		Type& getInfo(){ return info; }
		Node* getPrev(){ return prev; }
		Node* getNext(){ return next; }
}; //end Node


//pocetak lista
template<typename Type>
class Lista2
{
	public:
		//iterator
		struct iterator;
		
		//konstruktori
		Lista2();
		Lista2( const Lista2<Type>& );
		Lista2( Lista2<Type>&& );
		
		//operatori
		const Lista2<Type>& operator=( const Lista2<Type>& );
		const Lista2<Type>& operator=( Lista2<Type>&& );
		
		//destruktor
	    ~Lista2();
	    
		//metodi
		Lista2<Type>& push_front( const Type& newItem );
		Lista2<Type>& push_back( const Type& newItem);
		void pop_back();
		void pop_front();
		void deleteNode( const Type& deleteItem );
		bool isEmpty();
		Type& front();
		Type& back();
		bool search( const Type& searchItem );
		int size();
		void destroyList();
		void print();
		iterator begin() const { return iterator(first);}
        iterator end() const { return iterator(nullptr);}
		
	protected:
		Node<Type>* first;
		Node<Type>* last;
		int count;
	
	private:
		void copyList( const Lista2<Type>& );
			
};// end lista

//implementacija iteratora
template <typename Type>
   struct Lista2<Type>::iterator{
     Node<Type> * p_node;
     typedef std::bidirectional_iterator_tag iterator_category;
     typedef Type value_type;
     typedef size_t difference_type;
     typedef Type * pointer;
     typedef Type & reference;

     iterator(Node<Type> * n) : p_node(n) {}

     bool operator==(iterator const & it)  const {
       return p_node == it.p_node;
     }

     bool operator!=(iterator const & it) const {
       return !((*this)==it);
     }
     reference operator*(){ return p_node->getInfo(); }
     reference operator*() const { return p_node->getInfo(); }
     iterator & operator++(){
       p_node = p_node->getNext();
       return *this;
     }
     iterator operator++(int){
       if(p_node->getNext()==nullptr){
         Node<Type> *temp;
         temp=p_node;
         p_node=p_node->getNext();
         return iterator(temp);
       }
       p_node = p_node->getNext();
       return iterator(p_node->getPrev());
       //return p_node->prev_node;
     }

   };

//implementacija metoda
template<typename Type>
void Lista2<Type>::print()
{
	Node<Type>* temp;
	temp = this->first;
	while ( temp != nullptr )
	{
		cout << (*temp).getInfo() << " ";
		temp=(*temp).getNext();
	}
}
template<typename Type>
void Lista2<Type>::copyList( const Lista2<Type>& otherList )
{
	if(otherList.first == nullptr){
        first = last = nullptr;
    }

    else 
	{
        Node<Type> *newNode;
        Node<Type> *temp;

        temp = otherList.first;
        this->count = otherList.count;
        first = new Node<Type>;
        first -> setInfo(temp->getInfo());
        first -> setNext(nullptr);
        first -> setPrev(temp->getPrev());
        last = first;
        temp = temp -> getNext();
        while(temp != nullptr)
		{
            newNode = new Node<Type>;
            newNode -> setInfo(temp->getInfo());
            newNode -> setNext(nullptr);
            newNode -> setPrev(last);
            last -> setNext(newNode);
            last = newNode;
            temp = temp -> getNext();
		}
	}
}

template<typename Type>
void Lista2<Type>::destroyList()
{
	Node<Type>* temp;
	while( this->first != nullptr )
	{
		temp = this->first;
		first=first->getNext();
		delete temp;
	}
	last=nullptr;
	count=0;
}

template<typename Type>
int Lista2<Type>::size()
{
	int brojac=0;
	for ( auto i=this->begin(); i!= this->end(); ++i)
	brojac++;
	return brojac;
}

template<typename Type>
bool Lista2<Type>::search( const Type& searchItem )
{
	bool found=false;
	Node<Type>* temp;
	temp=this->first;
	
	while ( temp != nullptr && !found )
	{
		if( temp->getInfo() == searchItem )
			found=true;
		else
			temp=(*temp).getNext();
	}
	return found;
}

template<typename Type>
Type& Lista2<Type>::back()
{
	return this->last->getInfo();
}

template<typename Type>
Type& Lista2<Type>::front()
{
	return this->first->getInfo();
}

template<typename Type>
bool Lista2<Type>::isEmpty()
{
	if(first==nullptr)
		return true;
	return false;
}

template<typename Type>
void Lista2<Type>::deleteNode( const Type& deleteItem )
{
	bool found;
	Node<Type>* temp;
	
	if ( this->first == nullptr ) 
		throw string (" Cannot delete from an empty list ");
	else
	{
		if ( this->first->getInfo() == deleteItem ) 
			pop_front();
		else if ( this->last->getInfo() == deleteItem )
			pop_back();
		else
		{
			found=false;
			temp=this->first->getNext();
			
			while ( temp != nullptr & !found )
			{
				if( (*temp).getInfo() != deleteItem )
				temp=(*temp).getNext();
				else
				found=true;
			}
			if(found)
			{
				(temp->getPrev()->setNext(temp->getNext()));
				(temp->getNext()->setPrev(temp->getPrev()));
				this->count--;
				
				delete temp;
			}
			else 
			cout << "The item to be deleted is not in the list" << endl;
		}
	}
}

template<typename Type>
void Lista2<Type>::pop_back()
{
	if( this->last == nullptr ) throw string(" Cannot pop from an empty list");
	
	Node<Type>* temp;
	temp=this->last;
	this->last = this->last->getPrev();
	this->last->setNext( nullptr );
	delete temp;
	
	this->count--;
	
	if ( this->last == nullptr )
	first = last;

}

template<typename Type>
void Lista2<Type>::pop_front()
{
	if( this->first == nullptr ) throw string(" Cannot pop from an empty list ");
	
	Node<Type>* temp;
	
	temp=first->getNext();
	delete first;
	first=temp;
	
	this->count--;
	if( first == nullptr )
	last=first;
}

template<typename Type>
Lista2<Type>& Lista2<Type>::push_back( const Type& newItem )
{
	Node<Type>* newNode;
	newNode= new Node<Type>;
	newNode->setInfo( newItem );
	
	if(isEmpty()){
        first = last = newNode;
        first -> setPrev( nullptr );
        newNode -> setNext( nullptr );
        count++;
    }
    else {
        last -> setNext(newNode);
        newNode -> setPrev(last);
        newNode -> setNext(nullptr);
        last = newNode;
        count++;
    }
	return *this;
	
}
template<typename Type>
Lista2<Type>& Lista2<Type>::push_front( const Type& newItem )
{
	if(isEmpty())
	push_back( newItem );
	else
	{
		Node<Type>* newNode;
		newNode = new Node<Type>;
		newNode->setInfo( newItem );
		
		newNode->setNext( this->first );
		newNode->setPrev( nullptr );
		this->first->setPrev(newNode);
		this->first=newNode;
		
		this->count++;
	}
	return *this;
}

//implementacija destruktora
template<typename Type>
Lista2<Type>::~Lista2()
 {
 	destroyList();
 }

//implementacije operatora
template<typename Type>
const Lista2<Type>& Lista2<Type>::operator=( const Lista2<Type>& otherList )
{
	if( this != &otherList )
	{
		copyList( otherList );
	}
	return *this;
}

template<typename Type>
const Lista2<Type>& Lista2<Type>::operator=( Lista2<Type>&& otherList )
{
	swap(first,otherList.first);
	otherList.first=nullptr;
	
	return *this;
}


//implementacije konstruktora
template<typename Type>
Lista2<Type>::Lista2()
{
	first=nullptr;
	last=nullptr;
	count=0;
}

template<typename Type>
Lista2<Type>::Lista2( const Lista2<Type>& otherList )
{
	first=nullptr;
	copyList(otherList);
}

template<typename Type>
Lista2<Type>::Lista2( Lista2<Type>&& otherList )
{
	swap(first,otherList.first);
	otherList.first=nullptr;
}

#endif
