#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "ctest.h"

int main(void)
{
	void *lib_handle = NULL;
	void (*pctest1)(int *) = NULL;
	void (*pctest2)(int *) = NULL;
	char *error = NULL;

	// reset errors
	dlerror();

	lib_handle = dlopen("/tmp/lib/libctest.so", RTLD_LAZY);
	error = dlerror();
	if (NULL == lib_handle || error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(1);
	} 

	dlerror();

	pctest1 = dlsym(lib_handle, "ctest1");
	error = dlerror();
	if (NULL == pctest1 || error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(1);
	}
	
	dlerror();

	pctest2 = dlsym(lib_handle, "ctest2");
	error = dlerror();
	if (NULL == pctest2 || error != NULL) {
		fprintf(stderr, "%s\n", error);
	}

	int x = 0;
	pctest1(&x);
	printf("ctest1() -> %d\n", x);
	pctest2(&x);
	printf("ctest2() -> %d\n", x);

	dlclose(lib_handle);

	return 0;
}
