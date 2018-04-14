#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shape.hpp"

using namespace std;
// our global factory for making shapes
map<string, maker_t *> factory;


void show_circle();
void show_square();
void show_triangle();

int main(int argc, char **argv)
{
	// factory iterator
	//map<string, maker_t *>::iterator fitr;
	//TODO: implement more handy using of the factory pattern
	// show factory state	
	cout << "our factoru has got : " << factory.size() << " entities now" << endl;
	show_circle();
	// show factory state	
	cout << "new one appiered: " << factory.size() << " entity now" << endl;
	show_square();
	// show factory state	
	cout << "anoter one: " << factory.size() << " entities now" << endl;
	show_triangle();
	// show factory state	
	cout << "and last one: " << factory.size() << " entities now" << endl;
	return 0;
}

void show_circle()
{
	void *circle_lib_handle = NULL;
	char *error = NULL;
	shape *circle = NULL;
	// reset errors
	dlerror();
	// get lib handle
	circle_lib_handle = dlopen("./libcircle.so", RTLD_LAZY);
	error = dlerror();
	if (NULL == circle_lib_handle || error != NULL) {
		cerr << "[E] DYNLIB: " << error << endl;
		exit(1);
	} 
	// create an object of circle class by factory
	circle = factory["circle"]();
	// use a method of the class cicrle
	circle->draw();
	// free memory after use
	delete circle;
	// close lib handle	
	dlclose(circle_lib_handle);
}

void show_square()
{
	void *square_lib_handle = NULL;
	char *error = NULL;
	shape *square = NULL;
	// reset errors
	dlerror();
	// get lib handle
	square_lib_handle = dlopen("./libsquare.so", RTLD_LAZY);
	error = dlerror();
	if (NULL == square_lib_handle || error != NULL) {
		cerr << "[E] DYNLIB: " << error << endl;
		exit(1);
	} 
	// create an object of circle class by factory
	square = factory["square"]();
	// use a method of the class cicrle
	square->draw();
	// free memory after use
	delete square;
	// close lib handle	
	dlclose(square_lib_handle);
}


void show_triangle()
{
	void *triangle_lib_handle = NULL;
	char *error = NULL;
	shape *triangle = NULL;
	// reset errors
	dlerror();
	// get lib handle
	triangle_lib_handle = dlopen("./libtriangle.so", RTLD_LAZY);
	error = dlerror();
	if (NULL == triangle_lib_handle || error != NULL) {
		cerr << "[E] DYNLIB: " << error << endl;
		exit(1);
	} 
	// create an object of circle class by factory
	triangle = factory["triangle"]();
	// use a method of the class cicrle
	triangle->draw();
	// free memory after use
	delete triangle;
	// close lib handle	
	dlclose(triangle_lib_handle);
}


