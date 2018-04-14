#
# ei lib test how ot use functions
#
default:
	make all
#    
# build eitest with erl_interface static lib
eitest: eitest.o
	gcc -o eitest -I/usr/local/lib/erlang/lib/erl_interface-3.10.1/include -L/usr/local/lib/erlang/lib/erl_interface-3.10.1/lib eitest.o -pthread -lerl_interface -lei -lnsl

eitest.o:
	gcc -o eitest.o -c -I/usr/local/lib/erlang/lib/erl_interface-3.10.1/include main.c
#
# List files in library: 
lla:
	ar -t /usr/local/lib/erlang/lib/erl_interface-3.10.1/lib/libei.a
	ar -t /usr/local/lib/erlang/lib/erl_interface-3.10.1/lib/liberl_interface.a

all: lla eitest 

clean:
	rm *.o eitest 

