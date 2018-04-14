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
	make all

#testgw: testgw.o
#	gcc -rdynamic -o testgw main.o $(LIBS)

#testgw.o:
#	gcc -Wall -o testwg.o -c main.c
#    
# build cnode with erl_interface static lib and dynload lib mechanism
# it very inpotant to add a every places in -I and -L params
# I have an erorr linking while stay not added this params -I. -L.
testgw: testgw.o
	g++ -rdynamic -o testgw -I/usr/local/lib/erlang/lib/erl_interface-3.10.1/include -L/usr/local/lib/erlang/lib/erl_interface-3.10.1/lib testgw.o -pthread -lerl_interface -lei -lnsl -ldl -I. -L.

testgw.o:
	g++ -o testgw.o -c -I/usr/local/lib/erlang/lib/erl_interface-3.10.1/include main.cpp

# List files in library: 
# ar -t libctest.a
lla:
	ar -t /usr/local/lib/erlang/lib/erl_interface-3.10.1/lib/libei.a
	ar -t /usr/local/lib/erlang/lib/erl_interface-3.10.1/lib/liberl_interface.a


libcircle.so:  circle.o
	$(CC) -shared -Wl,-soname,libcircle.so.1 -o libcircle.so.1.0 circle.o

libsquare.so:  square.o
	$(CC) -shared -Wl,-soname,libsquare.so.1 -o libsquare.so.1.0 square.o

#added
libtriangle.so: triangle.o
	g++ -shared -Wl,-soname,libtriangle.so.1 -o libtriangle.so.1.0 triangle.o

# added
triangle.o:
	g++ -Wall -fPIC -c triangle.cpp

# fixed
circle.o:
	g++ -Wall -fPIC -c circle.cpp
# fixed
square.o:
	g++ -Wall -fPIC -c square.cpp

veil:
	erlc -W veil.erl

all: testgw libcircle.so libsquare.so libtriangle.so veil

ref:
	ln -sf ./libcircle.so.1.0 ./libcircle.so.1
	ln -sf ./libcircle.so.1 ./libcircle.so
	ln -sf ./libsquare.so.1.0 ./libsquare.so.1
	ln -sf ./libsquare.so.1 ./libsquare.so
	ln -sf ./libtriangle.so.1.0 ./libtriangle.so.1
	ln -sf ./libtriangle.so.1 ./libtriangle.so
#FIXME:added me just for example
# it has to be placed in a little more appropriate directory :)
#install:
#	mv libcircle.so.1.0 /tmp/lib
#	ln -sf /tmp/lib/libcircle.so.1.0 /tmp/lib/libcircle.so.1
#	ln -sf /tmp/lib/libcircle.so.1	/tmp/lib/libcircle.so
#	mv libsquare.so.1.0 /tmp/lib
#	ln -sf /tmp/lib/libsquare.so.1.0 /tmp/lib/libsquare.so.1
#	ln -sf /tmp/lib/libsquare.so.1	/tmp/lib/libsquare.so

clean:
	rm -f *.so *.so.* *.o *.beam testgw /tmp/lib/*
