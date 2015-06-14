#ifndef _LISTOFORDERS_H
#define _LISTOFORDERS_H
#include <iostream>
#include <ctime>
#include "lista2.h"
#include "order.h"

using namespace std;

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
    if ( date.getDay()>30 ){
      date.setMonth( date.getMonth() + 1 );
      date.setDay( 1 );
    }
    if ( date.getMonth() > 12 ){
      date.setYear( date.getYear() + 1 );
      date.setMonth ( 1 );
    }
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
  cout << "trenutni: " << current << endl;
  return current;
}//end function


//start of class definition
class ListOfOrders : public Lista2<Order>{
 
  public:
    void addNewOrder( Order& newItem );
    Date& findFreeDate();
    void deleteOrder(int _ID , int day , int month , int year , int hour );
    void printOrders();
};
// end of class definition

//implementing of methods
Date& ListOfOrders::findFreeDate(){
    
    Node<Order> *temp;  

    static  Date newDate = getCurrentDate(); //getting current date
    incrementDate( newDate ); 

    if ( newDate < (first->getInfo()).getDate() ) // if there is a free date before next order
      return newDate;
    else
    {
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
    }
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
      this->push_front( newItem );                  //if the new order needs to be placed first
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


void ListOfOrders::printOrders(){
  Node<Order> *temp;
  temp=first;
  while ( temp!=nullptr ){
    cout << temp->getInfo() << endl;
    temp=temp->getNext();
  }
}
#endif
