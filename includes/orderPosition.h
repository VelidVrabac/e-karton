#ifndef _ORDERPOSITION_H
#define _ORDERPOSITION_H

#include "../structures/queue.h"
#include <iostream>

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
		friend ostream& operator<<(ostream& o, const orderPosition& e){      
      	o<<"ID '"<<e._ID<<"' find on " << e._position.size() << " places: "<<endl;            
         o<<e._position<<endl;            
         return o;
  			}
};

#endif
