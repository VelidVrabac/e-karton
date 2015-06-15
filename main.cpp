#include <iostream>
#include <string>
#include "includes/ListofOrders.h"

using namespace std;

int main(){
  Date datum( 15 , 6 , 2015, 9 );
  Order novi( 1543 , "mirsad" , "ribic" );
  novi.setDate( datum );
  ListOfOrders lista;
  lista.addNewOrder( novi );
  cout << "dodan novi" << endl;
  Order novi2( 1544 , "mirnes" , "ribic" );
  Order novi3( 1545 , "mirnes" , "ribic" );
  lista.addNewOrder( novi2 );
  cout << "dodan novi2 " << endl;
  lista.addNewOrder( novi3 );
  cout << "dodan novi3 " << endl;
  Order novi4 ( 1533 , "novi" , "je" );
  Date datum2 ( 16 , 6 , 2015 , 9 );
  novi4.setDate(datum2);
  lista.addNewOrder(novi4);
  Order novi5 ( 2345 , "josnovih" , "aa" );
  lista.addNewOrder( novi5 );
  lista.printOrders();
  


}
