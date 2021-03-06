/*
 * syscall.c: code related to system calls
 */
#include "syscall.h"
#include "sys/socket.h"

void puts(char *string)
{
	display(string);
}

void putc(char val)
{
	char str[2];
	str[0] = val;
	str[1] = '\0';
	display(str);
}

int getchar(void)
{
	int retval;
	__asm__ __volatile__("svc #3\n"
	                     "mov %[rv], a1"
	                     : /* output operands */[ rv ] "=r"(retval)
	                     : /* input operands */
	                     : /* clobbers */ "a1", "a2", "a3", "a4");
	return retval;
}

int runproc(char *imagename, int flags)
{
	int retval;
	__asm__ __volatile__("svc #4\n"
	                     "mov %[rv], a1"
	                     : /* output operands */[ rv ] "=r"(retval)
	                     : /* input operands */
	                     : /* clobbers */ "a1", "a2", "a3", "a4");
	return retval;
}

int getpid(void)
{
	int retval;
	__asm__ __volatile__("svc #5\n"
	                     "mov %[rv], a1"
	                     : /* output operands */[ rv ] "=r"(retval)
	                     : /* input operands */
	                     : /* clobbers */ "a1", "a2", "a3", "a4");
	return retval;
}

int socket(int domain, int type, int protocol)
{
	int retval;
	__asm__ __volatile__("svc #6\n"
	                     "mov %[rv], a1"
	                     : /* output operands */[ rv ] "=r"(retval)
	                     : /* input operands */
	                     : /* clobbers */ "a1", "a2", "a3", "a4");
	return retval;
}

int bind(int sockfd, const struct sockaddr *address, socklen_t address_len)
{
	int retval;
	__asm__ __volatile__("svc #7\n"
	                     "mov %[rv], a1"
	                     : /* output operands */[ rv ] "=r"(retval)
	                     : /* input operands */
	                     : /* clobbers */ "a1", "a2", "a3", "a4");
	return retval;
}

int connect(int sockfd, const struct sockaddr *address, socklen_t address_len)
{
	int retval;
	__asm__ __volatile__("svc #8\n"
	                     "mov %[rv], a1"
	                     : /* output operands */[ rv ] "=r"(retval)
	                     : /* input operands */
	                     : /* clobbers */ "a1", "a2", "a3", "a4");
	return retval;
}

int send(int sockfd, const void *buffer, size_t length, int flags)
{
	int retval;
	__asm__ __volatile__("svc #9\n"
	                     "mov %[rv], a1"
	                     : /* output operands */[ rv ] "=r"(retval)
	                     : /* input operands */
	                     : /* clobbers */ "a1", "a2", "a3", "a4");
	return retval;
}

int recv(int sockfd, void *buffer, size_t length, int flags)
{
	int retval;
	__asm__ __volatile__("svc #10\n"
	                     "mov %[rv], a1"
	                     : /* output operands */[ rv ] "=r"(retval)
	                     : /* input operands */
	                     : /* clobbers */ "a1", "a2", "a3", "a4");
	return retval;
}
