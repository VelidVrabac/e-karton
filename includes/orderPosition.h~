#ifndef _ORDERPOSITION_H
#define _ORDERPOSITION_H

#include "../structures/queue.h"
#include <iostream>
#include "functions.h"

class orderPosition {

	private:
		int _ID;
		queue<int> _position;		
	public:
		orderPosition() = default;
		orderPosition(const int& id) : _ID(id) {}
		orderPosition(const int& id, int pos) : _ID(id) { _position.push(pos); }

		orderPosition(const orderPosition& x) {
			_ID=x._ID;
			_position=x._position;
		}
	    queue<int>& getPosition() { return _position; }	
        int getID() { return _ID; }
		void addPosition(const int& pos) { _position.push(pos); }
		bool operator == (const orderPosition& op) const { return _ID == op._ID; }
		bool operator > (const orderPosition& op) const { return _ID > op._ID; }
    
		friend std::ostream& operator<<(std::ostream& o, const orderPosition& e){    
		 getinfo(); std::cout << " je bio " << e._position.size() << " puta." << std::endl;  
         o << std::endl;
         return o;
  		}
    
};

#endif
