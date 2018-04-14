// A C node server using long node names


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "erl_interface.h"
#include "ei.h"

#define BUFSIZE 1000

int main(int argc, char **argv) {

  unsigned char buf[BUFSIZE] = {0};              /* Buffer for incoming message */
  ErlMessage emsg = {0};                         /* Incoming message */

  ETERM *fromp = NULL;
	ETERM *tuplep = NULL;
	ETERM *fnp = NULL;
	ETERM *argp = NULL;
	ETERM *resp = NULL;
  int res;
	// remember! this function must be called first!
	erl_init(NULL, 0);

	
	tuplep = erl_format("{~a,~i}", "tobbe", 3928);
	printf("tuplep len: %d\n", erl_term_len(tuplep));	
	ETERM *empty_listp = erl_mk_empty_list();
	ETERM *concatlistp = erl_cons(tuplep, empty_listp);
	printf("concatlist len: %d\n", erl_length(concatlistp));
	ETERM *pattern1 = erl_format("{~a,A}", "tobbe");
	ETERM *pattern2 = erl_format("{~a,A}", "netobbe");

	if (erl_match(pattern1, tuplep)) {
		printf("match pattern1\n");
		ETERM *A = erl_var_content(pattern1, "A");
		erl_print_term(stdout, tuplep);
		printf("\n");
		erl_print_term(stdout, A);
		printf("\n");
		erl_free_term(A);
	}

	if (erl_match(pattern2, tuplep)) {
		printf("match pattern2\n");	
	}
	
	erl_free_term(pattern1);
	erl_free_term(pattern2);
	erl_free_term(empty_listp);
	erl_free_term(concatlistp);	
	erl_free_term(fromp); 
	erl_free_term(tuplep);
	erl_free_term(fnp); 
	erl_free_term(argp);
	erl_free_term(resp);
}

