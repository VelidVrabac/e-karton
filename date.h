#include<iostream>
#include<string>

#ifndef _DATE_H
#define _DATE_H

using namespace std;

class Date{

  friend ostream& operator<<(ostream& exit, const Date& d);

  private:
    int _Day;
    int _Month;
    int _Year;
  public:
    Date(): _Day(0), _Month(0), _Year(0) {}
    ~Date() = default;
    
    int getDay() const { return _Day; }
    int getMonth() const { return _Month; }
    int getYear() const { return _Year; }

    void setDay(int day) { _Day = day; }
    void setMonth(int month) { _Month = month; }
    void setYear(int year) { _Year = year; }

    void addDate(int, int , int);
};

void Date::addDate(int day, int month, int year){
  _Day = day;
  _Month = month;
  _Year = year;
}

ostream& operator<<(ostream& exit, const Date& d) {
  exit << d._Day << "." << d._Month << "." << d._Year << " " << endl;
  return exit;
}

#endif

