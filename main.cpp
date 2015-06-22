#include <iostream>
#include <string>
#include "includes/ListofOrders.h"
#include "includes/orderTree.h"
#include "includes/functions.h"
#include<time.h>

using namespace std;

int main(){
	cout << "Dobro jutro!" << endl;
	cout << "Dobro dosli u ambulantu," << endl;
	cout << "Dr. Kasim Jasarevic" << endl;
	cout << "------------------------------------------------------------------"<< endl;

	ListOfOrders lista;
	lista.loadUnfinished();
	orderTree ordersHistory;
	ordersHistory.load();

	cout << "Pogledajte danasnju listu narudzbi:" << endl;
	cout << endl;
	lista.printOrders();
  cout << "------------------------------------------------------------------" << endl;
	int VisitingHours = 1;
	bool promjene = false; 
 
	do{
    cout << "Prikazati Menu: (DA):  ";
    int izbor;
    string m;
    cin >> m;
    if(m == "DA" || m=="da" || m=="Da"){
      izbor = Menu();
    }
    else {
      izbor = 7;
    }
		switch(izbor) {

			case 1: {
                string ime, prezime;
                int id;
                cout << "Broj kartona: ";
				cin >> id;
                cout << "Ime: ";
				cin >> ime;
                cout << "Prezime: ";
				cin >> prezime;
                Order x(id, ime, prezime);
                lista.addNewOrder(x);
                cout << endl;
                cout << "-->Uspijesno ste dodali pacijenta." << endl;
                cout << endl;
                promjene = true;
                break;
              }

			case 2: {
        bool found = true;
				string ime, prezime;
				int id, sat, dan, mjesec, godina;
				cout << "Broj kartona: ";
				cin >> id;
				cout << "Ime: ";
				cin >> ime;
				cout << "Prezime: ";
				cin >> prezime;
        Order y(id , ime , prezime);
        while ( found ){
				  cout << "Unesite dan, mjesec, godinu i sat kad zelite narudzbu: ";
				  cin >> dan >> mjesec >> godina >> sat;
          while ( sat == 10 ){
            cout << "10h je vrijeme pauze , pokusajte ponovo: " << endl;
            cin >> sat;
          }
          while ( sat < 8 || sat > 15 ){
            cout << sat << "h je van radnog vremena , pokusajte ponovo: " << endl;
            cin >> sat;
          }

          y.setDate( dan , mjesec, godina , sat );
          if ( !lista.findDate( y.getDate() ) )
             found = false;
          else
             cout << " Datum se vec koristi , pokusajte ponovo : " << endl;
        }

				y.setDate(dan, mjesec, godina, sat);
				lista.addNewOrder(y);
        cout << endl;
        cout << "-->Uspiješno ste dodali pacijenta." << endl;
        cout << endl;
				promjene=true;
				break;
				}

			case 3: {
        if ( lista.isEmpty() ){
          cout << endl;
          cout << "Trenutno nemate nijedne narudzbe." << endl;
          cout << endl;

          break;
        }
				string diagnoze;
				int id;
				cout << "Unesite broj kartona pacijenta sa kojim ste zavrsili: " ;
				cin >> id;
				cout << endl;
				cout << "Unesite dijagnozu za zavrsenog pacijenta: " ;
        		cin.ignore();
				getline(cin, diagnoze);
       		    cin.clear();
        try{
          int line = lista.finishOrder(id, diagnoze);
          ordersHistory.addPosition(id,line);
          cout << endl;
          cout << "-->Završili ste pacijenta, dijagnoza postavljena." << endl;
          promjene = true;
        }
        catch(exception &e){
          cout << e.what();
          cout << endl;
        }
				break;
			}

			case 6: {
				VisitingHours = 0;
                if(promjene){
                  	lista.SaveUnfinished();
					ordersHistory.save();
                  }
                cout << "Kraj radnog vremena. Dovidjenja!" << endl;
                break;
              }

			case 4: {
				lista.printOrders();
				break;
				}

			case 5: {
				int id;
				cout << "Unesite broj kartona: ";
				cin >> id;
				cout << endl;
				ordersHistory.findPatient(id);
				break;
				}

     	 default:
              cout << "Pogresan izbor" << endl;
    }

  }while(VisitingHours);

  return 0;
}
