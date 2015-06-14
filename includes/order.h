#include<iostream>
#include<string>

#ifndef _ORDER_H
#define _ORDER_H

#include "date.h"

class Order{

  friend std::ostream& operator<<(std::ostream& exit, const Order& o);

  private:
    int _ID;
    std::string _FirstName;
    std::string _LastName;
    Date _date;
  public:
    Order(): _ID(0), _FirstName(""), _LastName("") {}
    ~Order() = default;
    Order(int id, const std::string& fname, const std::string& lname):
      _FirstName(fname), _LastName(lname), _ID(id) {}

    int getID() const { return _ID; }
    std::string getFirstName() const { return _FirstName; }
    std::string getLastName() const { return _LastName; }

    void setID(int id) { _ID = id; }
    void setFirstName(const std::string& fname) { _FirstName = fname; }
    void setLastName(const std::string& lname) { _LastName = lname; }
    void setDate(int, int, int, int);
    void setDate( const Date& otherDate );
    bool operator<(const Order& d) const;

    Date& getDate(){ return _date;}
};

std::ostream& operator<<(std::ostream& exit, const Order& o) {
  exit << "ID: " << o._ID << "\n"
    << "Ime: " << o._FirstName << "\n"
    << "Prezime: " << o._LastName << "\n" 
    << "Datum: " << o._date <<std::endl; 
  return exit;
}

void Order::setDate(int day, int month, int year, int hour) {
  _date.addDate(day, month, year, hour);
}

void Order::setDate( const Date& otherDate ){
  int day = otherDate.getDay();
  int month = otherDate.getMonth();
  int year = otherDate.getYear();
  int hour = otherDate.getHour();
  _date.addDate( day , month , year , hour );
}

bool Order::operator<(const Order& d) const {
  return _date < d._date;
}

#endif
