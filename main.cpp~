#include <iostream>
#include <string>
#include "includes/ListofOrders.h"
#include "includes/orderTree.h"
#include "includes/functions.h"
#include <time.h>

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
	if(lista.size() == 0)
		cout << "Danas nema narudžbi" << endl;
	else
		cout << "Imate " << lista.size() << " naručenih/a pacijenata za danas" << endl;
  	cout << "------------------------------------------------------------------" << endl;
	int VisitingHours = 1;
	bool promjene = false; 
 
	do{
    cout << "Odaberi opciju: [meni/(broj)]:  ";
    string izbor;
	cin >> izbor;
   	if(izbor == "meni")
		izbor = Menu();
		
		if(izbor == "1") {
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
				Date tmp = x.getDate();
                cout << endl;
                cout << "--> Uspiješno ste naručili pacijenta, " << tmp.getDay() << "." << tmp.getMonth() << "." << tmp.getYear() << " " << tmp.getHour() << "h" << endl;
				cout << endl;
                promjene = true;
              }

		else if(izbor == "2") {
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
				cout << "--> Uspiješno ste naručili pacijenta, " << dan << "." << mjesec << "." << godina << " " << sat << "h" << endl;
				cout << endl;
				promjene=true;
		}

		else if(izbor == "3") {
        if ( lista.isEmpty() ){
          cout << endl;
          cout << "Trenutno nemate nijedne narudzbe." << endl;
          cout << endl;

        }else {
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
				  cout << "--> Završili ste pacijenta, dijagnoza postavljena." << endl;
				  promjene = true;
				}
				catch(exception &e){
				  cout << e.what();
				  cout << endl;
				}
			}
		}
			else if( izbor == "7") {
				VisitingHours = 0;
                if(promjene){
                  	lista.SaveUnfinished();
					ordersHistory.save();
                  }
                cout << "Kraj radnog vremena. Dovidjenja!" << endl;
         
              }

			else if( izbor == "4" ) {
				if(lista.size() == 0) 
					cout << "Nemate naručenih pacijenata!" << endl;
				else				
					lista.printOrders();
				}
			else if( izbor == "5" ) {
				if(lista.size() == 0)
					cout << "Nemate naručenih pacijenata! " << endl;
				ListOfOrders temp = lista;
				temp.sort();
				temp.printOrders();
			}

			else if( izbor == "6" ) {
				int id;
				cout << "Unesite broj kartona: ";
				cin >> id;
				cout << endl;
				if(!ordersHistory.findPatient(id))
					cout << "Pacijent sa brojem kartona '" << id << "' nije nikad dolazio kod vas!" << endl;
			}
     	 else 
              cout << "Pogresan izbor" << endl;
    

  }while(VisitingHours);

  return 0;
}
