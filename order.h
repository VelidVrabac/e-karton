#include<iostream>
#include<string>

#ifndef _ORDER_H
#define _ORDER_H

#include "date.h"

using namespace std;

class Order{

  friend ostream& operator<<(ostream& exit, const Order& o);

  private:
    int _ID;
    string _FirstName;
    string _LastName;
    Date _date;
  public:
    Order(): _ID(0), _FirstName(""), _LastName("") {}
    ~Order() = default;
    Order(int id, const string& fname, const string& lname):
      _FirstName(fname), _LastName(lname), _ID(id) {}

    int getID() const { return _ID; }
    string getFirstName() const { return _FirstName; }
    string getLastName() const { return _LastName; }

    void setID(int id) { _ID = id; }
    void setFirstName(const string& fname) { _FirstName = fname; }
    void setLastName(const string& lname) { _LastName = lname; }
    void setDate(int, int, int);
};

ostream& operator<<(ostream& exit, const Order& o) {
  exit << "ID: " << o._ID << "\n"
    << "Ime: " << o._FirstName << "\n"
    << "Prezime: " << o._LastName << "\n" 
    << "Datum: " << o._date << endl;
  return exit;
}

void Order::setDate(int day, int month, int year) {
  _date.addDate(day, month, year);
}

#endif
