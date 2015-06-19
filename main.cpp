#include <iostream>
#include <string>
#include "includes/ListofOrders.h"
#include "includes/orderTree.h"

using namespace std;

int main(){

	orderTree stablo;

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
	for(int i = 0; i < 40; i++){
		Order x(1122, "Velid", "Vrabac");	
		lista.addNewOrder(x);

	}
  lista.printOrders();

	int pozicija;	
	pozicija = lista.finishOrder( 2345, "Glavobolja" );
	stablo.addPosition(2345, pozicija);
	pozicija = lista.finishOrder( 1543, "Bronhitis" );
	stablo.addPosition(1543, pozicija);

	for(int i = 0; i < 40; i++){
		int poz;
		poz = lista.finishOrder(1122, "testiranje");
		if(poz != -1)
			stablo.addPosition(1122, poz);			

	}




	cout << "za id: 2345 " << endl;
	stablo.findWord(2345);
	
	cout << "za id: 1544 " << endl;
	stablo.findWord(1544);

	cout << "za id: 1122 " << endl;
	stablo.findWord(1122);

  return 0;


}
