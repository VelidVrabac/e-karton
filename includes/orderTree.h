#ifndef _STABLO_RIJECI_H
#define _ORDERTREE_H

#include <iostream>
#include <string>
#include <fstream>
#include "../structures/binarySearchTree.hxx" 
#include "orderPosition.h"
#include "../structures/queue.h"
#include "functions.h"

class orderTree : public BstStablo<orderPosition>{

	public:
		bool findPatient(const int& id);
		bool addPosition(const int& id, int pos);
		void load();
		void save();
  private:
    void saveTree( const binaryTreeNode<orderPosition> *p );
    void writeTree( const binaryTreeNode<orderPosition> *p , ofstream& myfile );

};
void orderTree::load(){
		//reading from the file
  string file_name="positionsTree.txt";
  ifstream fs(file_name.c_str());
    if(!fs) {
          cout << "The file does not exist!" << endl;
              fs.close();
                  return;
    }
    else{
          string word;
          string pos;
          while(fs >> word) {
            int i=0;
            string id;
            while ( word[i] != '-' ){
             id+=word[i];
              ++i;   
            }
            ++i;
            orderPosition x( stoi(id) );
            for ( int j=i; j<word.size(); ++j ){
             if ( word[j]!='|' )
               pos+=word[j];
             else{
               x.addPosition( stoi(pos) );
               pos="";
             }
            }
            this->insert( x );
          }
              
            fs.close();
            return;
    }
}

void orderTree::save(){
  this->saveTree( this->root );
}


void orderTree::saveTree(const binaryTreeNode<orderPosition> *p){
	//spremanje iz stabla u fajl
  if ( p != nullptr ){
    string file_name="positionsTree.txt";
    ofstream myfile ( file_name );
    if ( myfile.is_open() )
        writeTree( p , myfile );

    myfile.close();
  }
}

void orderTree::writeTree( const binaryTreeNode<orderPosition> *p , ofstream& myfile ){
  if ( p!=nullptr ){
    orderPosition X;
    queue<int> pos;
    X = p->info;
    pos = X.getPosition();
    myfile << X.getID() << "-";
    while ( !pos.empty() ){
     myfile << pos.front() << "|";
      pos.pop();
    }
    myfile << "\n"; 

    writeTree( p->llink , myfile );
    writeTree( p->rlink , myfile );
  }
}

bool orderTree::findPatient(const int& id){
	orderPosition tmp(id, 0);
	binaryTreeNode<orderPosition> *current;	
	current = this->root;
	while (current != nullptr) {
		if (current->info == tmp) {
			queue<int> tmp_q;
			tmp_q = current->info.getPosition();
			std::string word = getLine(tmp_q.front());
			Order order;
			order = parse(word);
			std::cout << "Pacijent " << order.getFirstName() << " " << order.getLastName() << " je bio " << tmp_q.size() << " puta:" << std::endl;	
			while(!tmp_q.empty()){
				word = getLine(tmp_q.front());
				order = parse(word);
				printOrder(order);
				tmp_q.pop();
			}		
			return true;
		}
		else if (current->info > tmp)
			current = current->llink;
		else 
			current = current->rlink;
	}
	return false;
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
