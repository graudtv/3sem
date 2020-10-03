/* Полезные функции */
#ifndef _FREQUENT_FEATURES_H_
#define _FREQUENT_FEATURES_H_

#include <stdlib.h>
#include <stdarg.h>

/*  Prints info message to fout according to fmt
 *  If macro PROGRAM_NAME is defined, prints PROGRAM_NAME
 * before error message (i.e. output looks like "progname: info_message")
 *  If PROGRAM_NAME is defined, it should be a string literal or
 * should be defined as a name of previously declared global variable
 * with type char * / const char * / etc. The second way (using global variable)
 * allows to set programm name in runtime, modifying global variable
 *  Symbol '\n' is added after the message automatically */
void info(FILE* fout, const char *fmt, ...)
{
#ifdef PROGRAM_NAME
	fprintf(fout, "%s: ", (PROGRAM_NAME));
#endif

	va_list args;
	va_start(args, fmt);
	vfprintf(fout, fmt, args);
	va_end(args);

	fputc('\n', fout);	
}

/*  Same as info, but prints message to stderr
 * and terminates programm after printing */
void error(const char *fmt, ...)
{
#ifdef PROGRAM_NAME
	fprintf(stderr, PROGRAM_NAME ": ");
#endif

	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fputc('\n', stderr);
	exit(EXIT_FAILURE);
 }

/*  Copies file with file descriptor fd_src to file with
 * descriptor fd_dst
 *  Returns 0 if success, -1 otherwise */
int copyfile(int fd_src, int fd_dst)
{
	char buf[BUFSIZ];
	int n = 0;

	while ((n = read(fd_src, buf, BUFSIZ)) > 0) {
		char *bufend = buf + n;
		for (char *p = buf; p < bufend; p += n)
			if ((n = write(fd_dst, p, bufend - p)) < 0)
				break;
	}
	return n;
}

#endif // _FREQUENT_FEATURES_H_