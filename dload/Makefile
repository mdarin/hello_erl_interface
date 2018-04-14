#
#  Dynamic loading and un-loading of shared libraries using libdl
#
prog: shared
	gcc -rdynamic -o progdl prog.c -ldl
# Generate the shared library: 
#		gcc -shared -Wl,-soname,libctest.so.1 -o libctest.so.1.0 ctest1.o ctest2.o
shared: lib
	gcc -shared -Wl,-soname,libctest.so.1 -o libctest.so.1.0 ctest1.o ctest2.o
# Compile the library functions: 
# 	gcc -Wall -fPIC -c ctest1.c ctest2.c
# This generates the library libctest.so.1.0
lib:
	gcc -Wall -fPIC -c ctest1.c ctest2.c
#TODO: also, you may add install target into prog then whole process will be done just by make command. And make install won't need more
# Move to lib/ directory:
#    sudo mv libctest.so.1.0 /opt/lib
#    sudo ln -sf /opt/lib/libctest.so.1.0 /opt/lib/libctest.so.1
#    sudo ln -sf /opt/lib/libctest.so.1 /opt/lib/libctest.so
install:
	mv libctest.so.1.0 /tmp/lib
	ln -sf /tmp/lib/libctest.so.1.0 /tmp/lib/libctest.so.1
	ln -sf /tmp/lib/libctest.so.1	/tmp/lib/libctest.so
# Configure the library path (see below and choose one of three mechanisms).
# In this example we set the environment variable: 
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/lib

# I put the lib files to /tmp/lib in this example
# There is three way to setup the path to your lib
# But I don't decide what kind of way to go yet

clean:
	rm progdl *.o /tmp/lib/*

