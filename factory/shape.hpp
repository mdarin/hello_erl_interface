#ifndef SHAPE_H
#define SHAPE_H
#include <map>
#include <string>
// base class for all shapes
class shape {
public:
   virtual void draw()=0;
};
// typedef to make it easier to set up our factory
typedef shape *maker_t();
// our global factory
extern std::map<std::string, maker_t*, std::less<std::string> > factory;
#endif // SHAPE_H
