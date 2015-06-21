#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <string>
#include <fstream>
#include<iostream>

int Id, Hours, Day, Month, Year;
string Diagnosis,FirstName,LastName;


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


void parse(std::string &word, int *array) {
  Id = stoi(word.substr(0,array[0]));
  FirstName = word.substr(array[0] + 1, array[1] - array[0]-1);
  LastName = word.substr(array[1]+1, array[2]-array[1]-1);
  Hours = stoi(word.substr(array[2]+1, array[3]-array[2]-1));
  Day = stoi(word.substr(array[3]+1, array[4]-array[3]-1));
  Month = stoi(word.substr(array[4]+1, array[5]-array[4]-1));
  Year = stoi(word.substr(array[5]+1, array[6]-array[5]-1));
  Diagnosis = word.substr(array[6]+1, word.size());
}   

void parse(std::string &word){
  int j = 0;
  int array[8];
  for(int i = 0; i < word.size(); ++i) {
    if(word[i] == '-')
      array[j++] = i;
  }
  parse(word, array);
}

void getinfo(){
 std::cout << FirstName << " "<< LastName;
}

void printf(){
  std::cout << "Datum: " << Day << "." << Month << "." << Year << " u " << Hours << " sati." << std::endl;
  std::cout << "Dijagnoza: " << Diagnosis << std::endl;
  std::cout << std::endl;
}

#endif
