
# 
# Compiling and Linking Your Code
# 
# cc -c -I/usr/local/otp/lib/erl_interface-3.2.3/include myprog.c 
# ld -L/usr/local/otp/lib/erl_interface-3.2.3/lib myprog.o -lerl_interface -lei -o myprog
#
# http://erlang.org/doc/apps/erl_interface/ei_users_guide.html#building_terms_and_patterns
#
# About linkig error:FIXED! https://stackoverflow.com/questions/14185290/erl-interface-linker-error
# 
default:
	make all

veil:
	erlc -W veil.erl 

#    
#
#
cnode: cnode.o
	gcc -o cnode -I/usr/local/lib/erlang/lib/erl_interface-3.10.1/include -L/usr/local/lib/erlang/lib/erl_interface-3.10.1/lib cnode.o -pthread -lerl_interface -lei -lnsl #-lsocket

cnode.o:
	gcc -o cnode.o -c -I/usr/local/lib/erlang/lib/erl_interface-3.10.1/include main.c
# List files in library: 
# ar -t libctest.a
lla:
	ar -t /usr/local/lib/erlang/lib/erl_interface-3.10.1/lib/libei.a
	ar -t /usr/local/lib/erlang/lib/erl_interface-3.10.1/lib/liberl_interface.a
all: lla cnode veil

clean:
	rm *.o cnode *.beam

