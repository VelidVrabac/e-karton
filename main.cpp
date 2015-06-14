#include <iostream>
#include <string>
#include "ListofOrders.h"

using namespace std;

int main(){
  Date datum( 15 , 6 , 2015, 9 );
  Order novi( 1543 , "mirsad" , "ribic" );
  novi.setDate( datum );
  ListOfOrders lista;
  lista.addNewOrder( novi );
  Order novi2( 1544 , "mirnes" , "ribic" );
  Order novi3( 1545 , "mirnes" , "ribic" );
  lista.addNewOrder( novi2 );
  lista.addNewOrder( novi3 );
  lista.printOrders();


}
