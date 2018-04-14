// A C node server using long node names

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <dlfcn.h>
#include "erl_interface.h"
#include "ei.h"
#include "shape.hpp"

using namespace std;

#define BUFSIZE 1000
// our global factory for making shapes
map<string, maker_t *> factory;


extern "C" {

int my_listen(int port);
int foo(int arg);
int bar(int arg);

int main(int argc, char **argv) {
  struct in_addr addr = {0};                     /* 32-bit IP number of host */
  int port;                                /* Listen port number */
  int listen;                              /* Listen socket */
  int fd;                                  /* fd to Erlang node */
  ErlConnect conn = {0};                         /* Connection data */

  int loop = 1;                            /* Loop flag */
  int got;                                 /* Result of receive */
  unsigned char buf[BUFSIZE] = {0};              /* Buffer for incoming message */
  ErlMessage emsg = {0};                         /* Incoming message */

  ETERM *fromp = NULL;
	ETERM *tuplep = NULL;
	ETERM *fnp = NULL;
	ETERM *argp = NULL;
	ETERM *resp = NULL;
  int res;
  
  port = atoi(argv[1]);

  erl_init(NULL, 0);

	inet_aton("127.0.0.1", &addr);
	fprintf(stderr, "inet addr -> %s\n", "127.0.0.1");
	fprintf(stderr, "initialize...\n");
	cerr << "\t[dynamic load libs]" << endl;
	
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
	delete circle;
	// free memory after use
	//delete circle;
	// close lib handle	
	//dlclose(circle_lib_handle);

	fprintf(stderr, "\t[cnode gateway]\n");
	fprintf(stderr, "node\n");
  if (erl_connect_xinit("cn1", "cnode", "cnode@127.0.0.1", 
			&addr, "cookie", 0) == -1)
    erl_err_quit("erl_connect_xinit");
	
	fprintf(stderr, "socket\n");
  /* Make a listen socket */
  if ((listen = my_listen(port)) <= 0)
    erl_err_quit("my_listen");
	fprintf(stderr, "publish\n");
  if (erl_publish(port) == -1)
    erl_err_quit("erl_publish");
	fprintf(stderr, "accept\n");
  if ((fd = erl_accept(listen, &conn)) == ERL_ERROR)
    erl_err_quit("erl_accept");
  fprintf(stderr, "Connected to %s\n\r", conn.nodename);
	fprintf(stderr, "main loop\n");

  while (loop) {

    got = erl_receive_msg(fd, buf, BUFSIZE, &emsg);
	
    if (got == ERL_TICK) {
			fprintf(stderr, "ERL_TICK\n");
      /* ignore */
    } else if (got == ERL_ERROR) {
			fprintf(stderr, "ERL_ERROR\n");
			// unload library
			// free memory after use
			//delete circle;
			// close lib handle	
			dlclose(circle_lib_handle);
      loop = 0;
    } else {
			fprintf(stderr, "GOT ELSE...\n");
			if (emsg.type == ERL_REG_SEND) {
				fprintf(stderr, "ERL_REG_SEND\n");
				fromp = erl_element(2, emsg.msg);
				tuplep = erl_element(3, emsg.msg);
				fnp = erl_element(1, tuplep);
				argp = erl_element(2, tuplep);

				if (strncmp(ERL_ATOM_PTR(fnp), "foo", 3) == 0) {
					cerr << "foo" << endl;
					res = foo(ERL_INT_VALUE(argp));
				} else if (strncmp(ERL_ATOM_PTR(fnp), "bar", 3) == 0) {
					res = bar(ERL_INT_VALUE(argp));
					cerr << "bar" << endl;
	
				} else if (strcmp(ERL_ATOM_PTR(fnp), "square") == 0) {
					res = 777;//circle->s();
					cerr << "draw" << endl;

					shape *s = factory["circle"]();
					s->draw();
					delete s;
				}
				cerr << "res -> " << res << endl;
				resp = erl_format("{cnode, ~i}", res);
				cerr << "sending response..." << endl;
				erl_send(fd, fromp, resp);
				cerr << "free mem" << endl;
				erl_free_term(emsg.from); 
				erl_free_term(emsg.msg);
				erl_free_term(fromp); 
				erl_free_term(tuplep);
				erl_free_term(fnp); 
				erl_free_term(argp);
				erl_free_term(resp);
				cerr << "mem is free now!" << endl;
      }
    }
  }
}

  
int my_listen(int port) 
{
  int listen_fd;
  struct sockaddr_in addr = {0};
  int on = 1;

  if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return (-1);

  setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

//%  memset((void*) &addr, 0, (size_t) sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(listen_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
    return (-1);

  listen(listen_fd, 5);
  return listen_fd;
}

int foo(int arg)
{
	return arg * arg;
}

int bar(int arg)
{
	return arg + arg;
}

} // end extern "C"
