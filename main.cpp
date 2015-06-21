#include <iostream>
#include <string>
#include "includes/ListofOrders.h"
#include "includes/orderTree.h"
#include "includes/functions.h"
#include<time.h>

using namespace std;

int Id, Hours, Day, Month, Year;
string FirstName, LastName, Diagnosis;

int VisitingHours = 1;
bool promjene = false; 

void parse(string & word, int *array) {
  Id = stoi(word.substr(0,array[0]));
  FirstName = word.substr(array[0]+1, array[1]-array[0]-1);
  LastName = word.substr(array[1]+1, array[2]-array[1]-1);
  Hours = stoi(word.substr(array[2]+1, array[3]- array[2]-1));
  Day = stoi(word.substr(array[3]+1,array[4]-array[3]-1));
  Month = stoi(word.substr(array[4]+1, array[5]-array[4]-1));
  Year= stoi(word.substr(array[5]+1, array[6]-array[5]-1));
  Diagnosis = word.substr(array[6]+1,word.size());

}

void parse(string &word) {
  int j = 0;
  int array[8];
  for(int i = 0;i < word.size() ; ++i) {
    if(word[i] == '-'){
      array[j++] = i;
    }
  }
  parse(word, array);
}

int main(){
	cout << "Dobro jutro!" << endl;
	cout << "Dobro dosli u ambulantu," << endl;
	cout << "Dr. Sara Josh" << endl;
	cout << "------------------------------------------------------------------"<< endl;

	ListOfOrders lista;
	lista.loadUnfinished();
	orderTree ordersHistory;
	ordersHistory.load();

	cout << "Pogledajte danasnju listu narudzbi:" << endl;
	lista.printOrders();
 
	do{
		cout << "-----------------------------------------------------------------"<< endl;
		cout << "Unesite:" << endl;
		cout << "1 -Ako zelite naruciti novog pacijenta" << endl;
		cout << "2 -Ako zelite naruciti novog pacijenta u odredjeno vrijeme" << endl;
		cout << "3 -Ako ste zavrsili pacijenta i zelite upisati dijagnozu" << endl;
		cout << "4 -Ako ste zavrsili sa radnim vremenom" << endl;
		cout << "5 -Ako zelite pregledati sve narudzbe koje imate" << endl;
		cout << "6 -Ako vas zanima historija odredjenog pacijenta" << endl;
		cout << "-----------------------------------------------------------------"<< endl;
		int izbor;
		cin >> izbor;

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
                promjene = true;
                break;
              }

			case 2: {
				string ime, prezime;
				int id, sat, dan, mjesec, godina;
				cout << "Broj kartona: ";
				cin >> id;
				cout << "Ime: ";
				cin >> ime;
				cout << "Prezime: ";
				cin >> prezime;
				cout << "Unesite dan, mjesec, godinu i sat kad zelite narudzbu: ";
				cin >> dan >> mjesec >> godina >> sat;
				Order y(id, ime, prezime);
				y.setDate(dan, mjesec, godina, sat);
				lista.addNewOrder(y);
				promjene=true;
				break;
				}

			case 3: {
				string diagnoze;
				int id;
				cout << "Unesite broj kartona pacijenta sa kojim ste zavrsili: " ;
				cin >> id;
				cout << endl;
				cout << "Unesite dijagnozu za zavrsenog pacijenta: " ;
				cin >> diagnoze;
				int line=lista.finishOrder(id, diagnoze);
				ordersHistory.addPosition(id, line);
				promjene=true;
				break;
			}

			case 4: {
				VisitingHours = 0;
                if(promjene){
                  int odgovor;
                  cout << "Ukoliko zelite sacuvati vase promjene unesite 1" << endl;
                  cin >> odgovor;
                  if(odgovor == 1){
                    lista.SaveUnfinished();
					ordersHistory.save();
                    cout << "Promjene uspijesno sacuvane." << endl;
                  }
                  else {
                    cout << "Promjene nisu sacuvane." << endl;
                  }
                }
                cout << "Kraj radnog vremena. Dovidjenja!" << endl;
                break;
              }

			case 5: {
				lista.printOrders();
				break;
				}

			case 6: {
				int id;
				cout << "Unesite broj kartona pacijenta ciju historiju zelite pregledati: ";
				cin >> id;
				cout << endl;
				ordersHistory.findWord(id);
				break;
				}

     	 default:
              cout << "Pogresan izbor" << endl;
    }

  }while(VisitingHours);

  return 0;
}
