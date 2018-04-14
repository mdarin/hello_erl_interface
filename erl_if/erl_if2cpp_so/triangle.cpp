#include <iostream> 
#include "triangle.hpp"
using namespace std;

void triangle::draw(){
   // simple ascii square
   cout << endl;
   cout << "        *    " << endl;
   cout << "       * *   " << endl;
   cout << "      *   *  " << endl;
   cout << "     *     * " << endl;
   cout << "    *       *" << endl;
   cout << "    *********" << endl;
   cout << endl;
}

extern "C" {
	shape *maker() {
		return new triangle;
	}

	class proxy {
	public:
		proxy() {
			factory["triangle"] = maker;
		}
	};
	proxy p;
} 
