#include<iostream>
#include<string>

#ifndef _DATE_H
#define _DATE_H

class Date{

  friend std::ostream& operator<<(std::ostream& exit, const Date& d);

  private:
    int _Day;
    int _Month;
    int _Year;
    int _Hour;
  public:
    Date(): _Day(0), _Month(0), _Year(0), _Hour(0) {}
    Date( int day , int month , int year , int hour ){ _Day=day , _Month=month , _Year=year , _Hour = hour ;}
    ~Date() = default;
    
    int getDay() const { return _Day; }
    int getMonth() const { return _Month; }
    int getYear() const { return _Year; }
    int getHour() const { return _Hour;  }

    void setDay(int day) { _Day = day; }
    void setMonth(int month) { _Month = month; }
    void setYear(int year) { _Year = year; }
    void setHour(int hour) { _Hour = hour; }

    void addDate(int, int , int, int);
    bool operator<(const Date& d) const;
    bool operator==(const Date& d) const;
};

void Date::addDate(int day, int month, int year, int hour){
  _Day = day;
  _Month = month;
  _Year = year;
  _Hour = hour;
}

std::ostream& operator<<(std::ostream& exit, const Date& d) {
  exit << d._Day << "." << d._Month << "." << d._Year << " u "<< d._Hour << " sati." << std::endl;
  return exit;
}


bool Date::operator<(const Date& d) const {
  if ( this->getYear() != d.getYear() )
    return this->getYear() < d.getYear();
  else if ( this->getMonth() != d.getMonth() )
    return this->getMonth() < d.getMonth();
  else if ( this->getDay() != d.getDay() )
    return this->getDay() < d.getDay();
  else if ( this->getHour() != d.getHour() )
    return this->getHour() < d.getHour();
  else
    return false;
}

bool Date::operator==(const Date& d) const {
  if ( this->getYear() == d.getYear() && this->getMonth()==d.getMonth() && this->getDay()==d.getDay() && this->getHour()==d.getHour() )
    return true;
  else
    return false;
}


#endif

