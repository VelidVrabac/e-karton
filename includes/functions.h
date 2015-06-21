#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "order.h"

std::string getLine(int id){
	std::string txt;
	std::ifstream file ("orderHistory.txt", std::ios::binary|std::ios::in|std::ios::ate);
	if (file.is_open()) {
		file.seekg (id, std::ios::beg);
		std::getline(file, txt);    
		file.close();
	}
	return txt;	
}

Order parse(std::string input){
	std::string orderArray[8];	
	std::string parsed;
	std::stringstream input_stringstream(input);
	int counter = 0;
	while(getline(input_stringstream,parsed,'-') && counter < 8)
	{
			orderArray[counter] = parsed;
			counter++;
	}
	Date date(stoi(orderArray[4]), stoi(orderArray[5]), stoi(orderArray[6]), stoi(orderArray[3]));
	Order tmp(stoi(orderArray[0]), orderArray[1], orderArray[2]);
	tmp.setDiagnose(orderArray[7]);
	tmp.setDate(date);
	return tmp;
}

void printOrder(Order& order){
	Date datum = order.getDate();
  	std::cout << "Datum: " << datum.getDay() << "." << datum.getMonth() << "." << datum.getYear() << " u " << datum.getHour() << " sati." << std::endl;
  	std::cout << "Dijagnoza: " << order.getDiagnose() << std::endl;
  	std::cout << std::endl;
}

#endif
