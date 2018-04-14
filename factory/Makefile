#
# using a factory class, as in the factory design pattern
#
CC = g++
LIBS = -ldl
#OBJS = testdcl.o

#
# here we compile a dynamic load un-load library
# we were done with this in the last example(dload)
#
# fixed
#.cpp.o:
#	$(CC) -ggdb -c $<

default:
	make testdcl

testdcl: testdcl.o #fixed
	$(CC) -rdynamic -o testdcl testdcl.o $(LIBS)

testdcl.o:
	g++ -c -Wall -o testdcl.o main.cpp 

libcircle.so:  circle.o
	$(CC) -shared -Wl,-soname,libcircle.so.1 -o libcircle.so.1.0 circle.o

libsquare.so:  square.o
	$(CC) -shared -Wl,-soname,libsquare.so.1 -o libsquare.so.1.0 square.o

#added
libtriangle.so: triangle.o
	g++ -shared -Wl,-soname,libtriangle.so.1 -o libtriangle.so.1.0 triangle.o

# added
triangle.o:
	g++ -c -Wall -fPIC triangle.cpp

# fixed
circle.o:
	g++ -c -Wall -fPIC circle.cpp
# fixed
square.o:
	g++ -c -Wall -fPIC square.cpp

all: testdcl libcircle.so libsquare.so libtriangle.so 

ref:
	ln -sf ./libcircle.so.1.0 ./libcircle.so.1
	ln -sf ./libcircle.so.1 ./libcircle.so
	ln -sf ./libsquare.so.1.0 ./libsquare.so.1
	ln -sf ./libsquare.so.1 ./libsquare.so
	ln -sf ./libtriangle.so.1.0 ./libtriangle.so.1
	ln -sf ./libtriangle.so.1 ./libtriangle.so
#FIXME:added me just for example
# it has to be placed in a little more appropriate directory :)
install:
	mv libcircle.so.1.0 /tmp/lib
	ln -sf /tmp/lib/libcircle.so.1.0 /tmp/lib/libcircle.so.1
	ln -sf /tmp/lib/libcircle.so.1	/tmp/lib/libcircle.so
	mv libsquare.so.1.0 /tmp/lib
	ln -sf /tmp/lib/libsquare.so.1.0 /tmp/lib/libsquare.so.1
	ln -sf /tmp/lib/libsquare.so.1	/tmp/lib/libsquare.so

clean:
	rm -f *.so *.so.* *.o testdcl /tmp/lib/*
