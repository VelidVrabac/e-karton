#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <string>
#include <fstream>
std::string getLine(int id){
	string txt;
	ifstream file ("orderHistory.txt", ios::binary|ios::in|ios::ate);
	if (file.is_open()) {
		file.seekg (id, ios::beg);
		getline(file, txt);    
		file.close();
	}
	return txt;	
}

#endif
