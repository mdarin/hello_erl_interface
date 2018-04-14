#
# make for raw binary erlang port
# 
edemo_server:
	erlc -W demo_server.erl

demo_server: demo_server.o 
	gcc -o demo_server demo_server.o 

demo_server.o: 
	gcc -c -o demo_server.o main.c

all: demo_server edemo_server

#
# you should be a root
# OR ajust PATH in erl envin
install:
	mv demo_server /usr/bin


clean:
	rm demo_server.o demo_server demo_server.beam

