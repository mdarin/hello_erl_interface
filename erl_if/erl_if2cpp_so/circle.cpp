#include <iostream> 
#include "circle.hpp"
using namespace std;

void circle::draw(){
   // simple ascii circle<\n>
   //cout << "\n";
   //cout << "      ****\n";
   //cout << "    *      *\n";
   //cout << "   *        *\n";
   //cout << "   *        *\n";
   //cout << "   *        *\n";
   //cout << "    *      *\n";
   //cout << "      ****\n";
   //cout << "\n";

   cerr << "\n";
   cerr << "      ****\n";
   cerr << "    *      *\n";
   cerr << "   *        *\n";
   cerr << "   *        *\n";
   cerr << "   *        *\n";
   cerr << "    *      *\n";
   cerr << "      ****\n";
   cerr << "\n";
}


extern "C" {

	shape *maker() {
		return new circle;
	}

	class proxy {
	public:
  	proxy() {
    	// register the maker with the factory
			factory["circle"] = maker;
		}
	};

	// our one instance of the proxy
	proxy p;
}
