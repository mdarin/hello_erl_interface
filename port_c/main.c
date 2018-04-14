// пример из книжки по эрлангу
// адаптированнаый
// реализация порта erlang <-stdI/O-> c
// 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// -------------------------------------------
// WARNING!
// Message data are all unsigned bytes
// 
typedef unsigned char byte;

// -------------------------------------------
// Funcs protos
//
int read_cmd(byte *buf);
int write_cmd(byte *buf, int len);
int read_exact(byte *buf, int len);
int write_exact(byte *buf, int len);
void put_int16(short int i, byte *s);


/* -------------------------------------------
 * Read the 2 length bytes (MSB first), then the data.
 */
int read_cmd(byte *buf)
{
	int len;

	if (read_exact(buf, 2) != 2)
		return(-1);

	len = (buf[0] << 8) | buf[1];

	return read_exact(buf, len);
}

/* -------------------------------------------
 * Pack the 2 bytes length (MSB first) and send it
 */
int write_cmd(byte *buf, int len)
{
	byte str[2];

	put_int16(len, str);

	if (write_exact(str, 2) != 2)
		return(-1);

	return write_exact(buf, len);
}

/* -------------------------------------------
 * [read|write]_exact are used since they may return
 * BEFORE all bytes have been transmitted
 */
int read_exact(byte *buf, int len)
{
	int i = 0; 
	int got = 0;

	do {
		if ((i = read(0, buf+got, len-got)) <= 0)
			return (i);
		got += i;
	} while (got < len);

	return (len);
}

/* -------------------------------------------
 *
 */
int write_exact(byte *buf, int len)
{
	int i = 0; 
	int wrote = 0;
	
	do {
		if ((i = write(1, buf + wrote, len - wrote)) <= 0)
			return (i);
		wrote += i;
	} while (wrote < len);

	return (len);
}

/* -------------------------------------------
 *
 */
void put_int16(short int i, byte *s)
{
	*s = (i >> 8) & 0xff;
	s[1] = i & 0xff;
}


/* -------------------------------------------
 * main driver
 */
int main(int argc, char **argv) 
{
	int len = 0;
	int i = 0;
	char *progname = argv[0]; // Save start name of program 
	byte buf[1000] = {0};
	
	fprintf(stderr, "\n\n\tdemo_server in C Starting!\n\n");

	while ((len = read_cmd(buf)) > 0){
// • If the program is sent the string "echo" it sends the reply "ohce" to Erlang.
// • If the server is sent a data block whose first byte is 10 it replies with a block
//	 where all the elements in the block except the first have been doubled.
// • Otherwise the data is ignored.
		if(strncmp(buf, "echo", 4) == 0) {
			write_cmd("ohce", 4);
		} else if(buf[0] == 10) {
			for ( i = 1; i < len ; i++)
				buf[i] = 2 * buf[i];
			write_cmd(buf, len);
		} else {
			write_cmd("ignored", 7);
		}
	}

	return EXIT_SUCCESS;
}
