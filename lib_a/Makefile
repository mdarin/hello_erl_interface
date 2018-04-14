#
# Static Libraries: (.a) creation procedure
#
# Linking with the library:
#    cc -o executable-name prog.c libctest.a
#    cc -o executable-name prog.c -L/path/to/library-directory -lctest
porg: obj liba lla
	gcc -I./include -o prog prog.c ./lib/libctest.a
	gcc -L./lib -o prog prog.c -lctest
	 
# Compile: cc -Wall -c ctest1.c ctest2.c
# Compiler options:
#    -Wall: include warnings. See man page for warnings specified.
obj: 
	gcc -Wall -c ctest1.c ctest2.c

# Create library "libctest.a": 
#	ar -cvq libctest.a ctest1.o ctest2.o
liba: obj
	ar -cvq ./lib/libctest.a ctest1.o ctest2.o

# List files in library: 
# ar -t libctest.a
lla:
	ar -t ./lib/libctest.a

clean:
	rm *.o prog ./lib/*
