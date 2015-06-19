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
  /*
  cout << "id " << Id << endl;
  cout << "ime " << FirstName << endl;
  cout << "prezime " << LastName << endl;
  cout << "sat " << Hours << endl;
  cout << "dan " << Day << endl;
  cout << "mjesec " << Month << endl;
  cout << "godina " << Year<< endl;
  cout << "dijagnoza " << Diagnosis << endl;
  cout << "id+day " << Id+Day << endl; 
  */
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
  cout << "Welcome to main" << endl;
  ListOfOrders lista;
  //Order nova(1111, "Kasim", "Jasarevic");
  //Order nova1(1112, "Velid", "Vrabac");
  //Order nova2(1113, "Alma", "Avdic");
  //Order nova3(1114, "Mirsad", "Ribic");
  //lista.addNewOrder(nova);
  //lista.addNewOrder(nova1);
  //lista.addNewOrder(nova2);
  //lista.addNewOrder(nova3);
  //lista.SaveUnfinished();
  do{
    cout << "1. Naruci pacijenta" << endl;
    cout << "2. Zavrsi pacijena" << endl;
    cout << "3. Kraj radnog vremena" << endl;
    int izbor;
    cin >> izbor;
    switch(izbor) {
      case 1: {
                string ime, prezime;
                int id;
                cout << "ID: "; cin >> id;
                cout << "Ime: "; cin >> ime;
                cout << "Prezime: "; cin >> prezime;
                Order x(id, ime, prezime);
                lista.addNewOrder(x);
                promjene = true;
                break;
              }
      case 3: {
                VisitingHours = 0;
                if(promjene){
                  string odgovor;
                  cout << "Imate novih promjena, zelite ih sacuvati ?" << endl;
                  cout << "DA" << endl;
                  cout << "NE" << endl;
                  cin >> odgovor;
                  if(odgovor == "DA"){
                    lista.SaveUnfinished();
                    cout << "Promjene uspijesno sacuvane." << endl;
                  }
                  else {
                    cout << "Promjene nisu sacuvane." << endl;
                  }
                }
                cout << "Kraj radnog vremena. Dovidjenja" << endl;
                break;
              }
      default:
              cout << "Pogresan izbor" << endl;
    }
  }while(VisitingHours);
  return 0;
}
