#ifndef _LISTOFORDERS_H
#define _LISTOFORDERS_H
#include <iostream>
#include <string>
#include <ctime>
#include "../structures/lista2.h"
#include "order.h"
#include <fstream>
#include <stdexcept>

using namespace std;

int saveOrder( Node<Order>* found, const string& diagnoze){
	if(found != nullptr){	
		// saving finished order to history of orders
		ofstream fs("orderHistory.txt" , ios::app );
		if(!fs) {
			fs.close();
			return -1;
		}
		else{
			int line =  fs.tellp();
			Date date = found->getInfo().getDate();
			fs << found->getInfo().getID() << "-" << found->getInfo().getFirstName() << "-" << found->getInfo().getLastName()<< "-" << date.getHour() << "-" << date.getDay() << "-" << date.getMonth() << "-" << date.getYear() << "-" << diagnoze << "\n";   
			fs.close();
			return line;
		}
	}
	else{
		std::cout << "Not found order with this id!" << std::endl;
		return -1;
	}
}

//function begin
void incrementDate( Date& date ){
  date.setHour ( date.getHour() + 1 );
  if ( date.getHour() == 10 ){
    date.setHour( 11 );
    return;
  }
  else if ( date.getHour() > 15 ){
    date.setHour( 8 );
    date.setDay( date.getDay()+1 );

    if ( date.getMonth() == 2 && date.getDay()>28 ){
      date.setMonth( 3 );
      date.setDay( 1 );
    }

    if ( date.getMonth() == 4 || date.getMonth() == 6 || date.getMonth() == 9 || date.getMonth() == 11 ){
      if ( date.getDay() > 30 ){
        date.setMonth( date.getMonth() + 1 );
        date.setDay( 1 );
      }
    }
    else{
      if ( date.getDay() > 31 ){
        date.setMonth( date.getMonth() + 1 );
        date.setDay( 1 );
      }
    }
    if ( date.getMonth() > 12 ){
      date.setYear( date.getYear() + 1 );
      date.setMonth ( 1 );
    }
  }
  else if ( date.getHour() < 8 ){
    date.setHour(8);
  }
}


//function begin
Date& getCurrentDate(){
  time_t currentTime;
  struct tm *localTime;
  time( &currentTime );
  localTime=localtime( &currentTime );
  int Day   = localTime -> tm_mday;
  int Month = localTime -> tm_mon+1;          //function to get current time
  int Year  = localTime -> tm_year + 1900;
  int Hour  = localTime -> tm_hour;                 

  static Date current ( Day , Month , Year , Hour );
  return current;
}//end function


//start of class definition
class ListOfOrders : public Lista2<Order>{
 
  public:
    void addNewOrder( Order& newItem );
    Date& findFreeDate();
    int finishOrder(int ID , std::string diagnoze );
    void printOrders();
    void SaveUnfinished();
  	void loadUnfinished();
    bool findDate( Date& d );
	void sort();
};
// end of class definition

//implementing of methods

bool ListOfOrders::findDate( Date& d ){
  Node<Order> *temp;
  temp = first;
  while ( temp != nullptr ){
    if ( (temp->getInfo()).getDate() == d )
      return true;
    else
      temp=temp->getNext();
  }

   return false;
}
void ListOfOrders::sort(){

	Node<Order> *temp1,*temp2, *min;
    temp1 = first;
    while(temp1 != nullptr) {
		min = temp1;
		temp2 = temp1->getNext();
		while(temp2 != nullptr){
			if((temp2->getInfo()).getFirstName() < (min->getInfo()).getFirstName())
				min = temp2; 
			temp2=temp2->getNext();
		}
		if(min != temp1){
				Order x = temp1->getInfo();
				
					temp1->setInfo(min->getInfo());
					min->setInfo(x);
				}
		temp1 = temp1->getNext();
	}
}

Date& ListOfOrders::findFreeDate(){
    
    Node<Order> *temp;  

    static  Date newDate = getCurrentDate(); //getting current date
    incrementDate( newDate ); 
    if ( !isEmpty() ){
      if ( newDate < (first->getInfo()).getDate() ) // if there is a free date before next order
        return newDate;
      else{
         if ( first->getNext() != nullptr ){
            temp=first->getNext();
            while( temp!=nullptr ){
              Date date1 = ((temp->getPrev())->getInfo()).getDate();
              incrementDate ( date1 );
              Date date2 = (temp->getInfo()).getDate();
              if ( date1 < date2 ){
              newDate.addDate( date1.getDay() , date1.getMonth() , date1.getYear() , date1.getHour() );
              return newDate;
              }
              else{
              temp=temp->getNext();
              }
            }
            if ( temp == nullptr ){
              Date date = (last->getInfo()).getDate();
              newDate.addDate(date.getDay() , date.getMonth() , date.getYear() , date.getHour());
              incrementDate(newDate);
              return newDate;
            }
            else
              return newDate;
         }
         else{
            static Date date=(first->getInfo()).getDate();
            incrementDate( date );
            return date;
         }
      }
    }
    else
      return newDate;
}

int ListOfOrders::finishOrder( int ID, std::string diagnoze ){
	Node<Order> *temp;
  	temp=first;
	int order_line = -1;	
	if ( this->first == nullptr ){
		std::cout << " You do not have orders! " << std::endl;
		return -1;	
	}
	else
	{
		if ( this->first->getInfo().getID() == ID ){
			order_line = saveOrder(first, diagnoze);			
			pop_front();
		}
		else if ( this->last->getInfo().getID() == ID ){
			order_line = saveOrder(last, diagnoze);		
			pop_back();
		}
		else
		{
  			while ( temp!=nullptr ){
				if((temp->getInfo()).getID() == ID){ //find order with requested id
					// delete order
					order_line = saveOrder(temp, diagnoze);
					temp->getPrev()->setNext( temp->getNext() ); 
					temp->getNext()->setPrev( temp->getPrev() );
					temp->setPrev( nullptr );
					temp->setNext( nullptr );
					delete temp;
					temp = nullptr;		
				}
				else
					temp=temp->getNext();
			}
				  if(temp == nullptr)
				  throw domain_error("ID not found, or the patient is not on the list.");
  		}
	}
	return order_line;
}


void ListOfOrders::addNewOrder( Order& newItem ){
  if ( (newItem.getDate()).getYear() == 0 ){
    Date newDate = this->findFreeDate();
    newItem.setDate( newDate );           //if there is no date given
  }
  Node<Order> *temp;
  Node<Order> *newNode;
  newNode = new Node<Order>;
  newNode->setInfo( newItem );
  if ( isEmpty() ){
    first = last = newNode;
    newNode->setNext( nullptr );
    newNode->setPrev( nullptr );
    ++count;
  }
  else if ( first->getNext() == nullptr ){
    Date date = (first->getInfo()).getDate();
    if ( newItem.getDate() < date )
      this->push_front( newItem );
    else
      this->push_back( newItem );
  }
  else{
    if ( newItem.getDate() < (first->getInfo()).getDate() ){
      this->push_front( newItem );      //if the new order needs to be placed first
    }
    else{
      temp=first->getNext();
      while ( temp!=nullptr ){
        if ( newItem.getDate() < (temp->getInfo()).getDate()){
          newNode->setNext( temp );
          newNode->setPrev( temp->getPrev());
          (temp->getPrev())->setNext( newNode );   //finding place for the new order
          temp->setPrev( newNode );
          ++count;
          break;
        }
        else{
          temp=temp->getNext();
        }
      }
      if ( temp == nullptr ){
      this->push_back( newItem ); // if the new order needs to be placed last
      }
   }
 }
}

void ListOfOrders::SaveUnfinished() {
  // Save the file
  ofstream UnfinishedOrder;
  UnfinishedOrder.open("UnfinishedOrder.txt"); 
  if(UnfinishedOrder.is_open()){
    Node<Order> *temp;
    temp = first;
    while(temp != nullptr) {
      Date date = temp->getInfo().getDate();
      Order person =  temp->getInfo();
      UnfinishedOrder << person.getID() << " " << person.getFirstName() << " " << person.getLastName() << " " 
        << date.getHour() << " " << date.getDay() << " " << date.getMonth() << " " << date.getYear();
      UnfinishedOrder << endl;
      temp = temp->getNext();
    }
    UnfinishedOrder.close();
  }
  else {
    cout << "There was an error opening the file." << endl;
    UnfinishedOrder.close();
    return;
  }
}


void ListOfOrders::loadUnfinished() {
		//reading from the file
	string file_name="UnfinishedOrder.txt";
	ifstream fs(file_name.c_str());
	if(!fs) {
		cout << "The file does not exist!" << endl;
			fs.close();
			return;
    }
	else{
		string word;
		int brojac=0;
		Order narudzba;
		Date datum;

		while(fs >> word) {
		if ( brojac == 0 ){
			narudzba.setID( stoi(word) );
			++brojac;
		}
		else if ( brojac == 1 ){
			narudzba.setFirstName ( word );
			++brojac;		
		}
		else if ( brojac == 2 ){
			narudzba.setLastName ( word );
			++brojac;		
		}
		else if ( brojac == 3 ){
			datum.setHour ( stoi(word) );
			++brojac;		
		}
		else if ( brojac == 4 ){
			datum.setDay ( stoi(word) );
			++brojac;		
		}
		else if ( brojac == 5 ){
			datum.setMonth ( stoi(word) );
			++brojac;		
		}
		else if ( brojac == 6 ){
			datum.setYear ( stoi(word) );
			narudzba.setDate ( datum );
			this->addNewOrder ( narudzba );
			brojac=0;
			}
		}
	}
}

void ListOfOrders::printOrders(){
  Node<Order> *temp;
  temp=first;
  while ( temp!=nullptr ){
    cout << temp->getInfo() << endl;
    temp=temp->getNext();
  }
}
#endif
