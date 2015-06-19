#ifndef _BST_H
#define _BST_H

#include <iostream>
#include	"binaryTree.hxx"
using namespace std;

template <class elemType>
class BstStablo: public binaryTree<elemType>
{
	public:
		bool search(const elemType& searchItem) const;		
		void insert(const elemType& insertItem);		
		void deleteNode(const elemType& deleteItem);				
	private:
		void deleteFromTree(binaryTreeNode<elemType>* &p);	

};

template <class elemType>
bool BstStablo<elemType>::search(const elemType& searchItem) const
{
	binaryTreeNode<elemType> *current; 
	bool found = false;
	if (this->root == nullptr)  
		cout << "Cannot search the empty tree." << endl;
	else
	{
		current = this->root; 
		while (current != nullptr && !found) 
		{
			if (current->info == searchItem) 
				found = true;
			else if (current->info > searchItem) 			
				current = current->llink;
			else
				current = current->rlink; 
		}
	}
	return found;
}

template <class elemType>
void BstStablo<elemType>::insert(const elemType& insertItem)
{
	binaryTreeNode<elemType> *current; 
	binaryTreeNode<elemType> *trailCurrent; 
	binaryTreeNode<elemType> *newNode; 
	newNode = new binaryTreeNode<elemType>(insertItem);
	if (this->root == nullptr){
		std::cout << "test ispis 1 problem xxx" << std::endl;
		this->root = newNode;
		std::cout << "test 1 ispis" << std::endl;
	}
	else
	{
		current = this->root;
		while (current != nullptr)
		{
			trailCurrent = current;
			if (current->info == insertItem)
			{
				cout << "Item already in list! Duplicates are  not allowed" <<endl;
				return;
			}
			
			else if (current->info > insertItem)
				current = current->llink;
			else 
				current = current->rlink;
		}
		if (trailCurrent->info > insertItem) 
			trailCurrent->llink = newNode;
		else 
			trailCurrent->rlink = newNode;
	}
}

template <class elemType>
void BstStablo<elemType>::deleteFromTree(binaryTreeNode<elemType>* &p)
{
	
	binaryTreeNode<elemType> *current;
	binaryTreeNode<elemType> *trailCurrent; 
	binaryTreeNode<elemType> *temp;
	if (p == nullptr) 
		cout << "Error: The node to be deleted is nullptr." << endl;
	else if(p->llink == nullptr && p->rlink == nullptr)
	{
		temp = p; 
		p = nullptr;
		delete temp;
	}
	else if(p->llink == nullptr)
	{
		temp = p;
		p = temp->rlink;
		delete temp;
	}
	else if(p->rlink == nullptr)
	{
		temp = p;
		p = temp->llink;
		delete temp;
	}
	else
	{
		current = p->llink;
		trailCurrent = nullptr;
		while (current->rlink != nullptr)
		{
			trailCurrent = current;
			current = current->rlink;
		}
		p->info = current->info;
		if (trailCurrent == nullptr)		
			p->llink = current->llink;
		else 
			trailCurrent->rlink = current->llink;
		delete current;
	}
}

template <class elemType>
void BstStablo<elemType>::deleteNode(const elemType& deleteItem)
{
	binaryTreeNode<elemType> *current;
	binaryTreeNode<elemType> *trailCurrent;
	bool found = false;
	if (this->root == nullptr)
		cout << "Cannot delete from the empty tree." << endl;
	else
	{
		current = this->root;
		trailCurrent = this->root;
		while (current != nullptr && !found)
		{
			if (current->info == deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				if (current->info > deleteItem) 
					current = current->llink;				
				else
					current = current->rlink;
			}
		}
	if (current == nullptr)
		cout << "The delete item is not in the tree." << endl;
	else if (found)
	{
		if (current == this->root)
			deleteFromTree(this->root);		
		else if (trailCurrent->info > deleteItem) 
			deleteFromTree(trailCurrent->llink);		
		else
			deleteFromTree(trailCurrent->rlink);
	}
	}
}

#endif
