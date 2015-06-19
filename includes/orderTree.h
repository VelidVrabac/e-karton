#ifndef _STABLO_RIJECI_H
#define _ORDERTREE_H

#include <iostream>
#include <string>
#include "../structures/binarySearchTree.hxx" 
#include "orderPosition.h"
#include "../structures/queue.h"
#include "functions.h"

class orderTree : public BstStablo<orderPosition>{

	public:
		void findWord(const int& id);
		bool addPosition(const int& id, int pos);
		void load();
		void save();
};
void orderTree::load(){
	//učitavanje iz fajla u stablo
}
void orderTree::save(){
	//spremanje iz stabla u fajl
}
void orderTree::findWord(const int& id){
	orderPosition tmp(id, 0);
	binaryTreeNode<orderPosition> *current;	
	current = this->root;
	while (current != nullptr) {
		if (current->info == tmp) {
			std::cout << current->info;
			queue<int> tmp_q;
			tmp_q = current->info.getPosition();
			while(!tmp_q.empty()){
				std::cout << getLine(tmp_q.front()) << std::endl;
				tmp_q.pop();
			}		
			return;
		}
		else if (current->info > tmp)
			current = current->llink;
		else 
			current = current->rlink;
	}
	std::cout << "ID: '" << id << "' not found!" << std::endl;
}
bool orderTree::addPosition(const int& id, int position){
	orderPosition element(id, position);
	binaryTreeNode<orderPosition> *current;
	binaryTreeNode<orderPosition> *trailCurrent;
	binaryTreeNode<orderPosition> *newNode;
	newNode = new binaryTreeNode<orderPosition>(element);
	if (this->root == nullptr){
		this->root = newNode;		
	}
	else {
		current = this->root;
		while (current != nullptr) {
			trailCurrent = current;
			if (current->info == element) {
			    current->info.addPosition(position);			
				return true;
			}
			else if (current->info > element)
				current = current->llink;
			else 
				current = current->rlink;
		}
		if (trailCurrent->info > element) 
			trailCurrent->llink = newNode;
		else 
			trailCurrent->rlink = newNode;
	}  
	return false;      
} 

#endif	
