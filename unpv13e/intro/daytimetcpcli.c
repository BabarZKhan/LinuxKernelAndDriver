// implementation of a TCP
// time-of-day client. This client establishes a TCP connection with a server and the
// server simply sends back the current time and date in a human-readable format



#include	"unp.h"

int
main(int argc, char **argv)
{
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");
		
If the call to socket fails, we abort the program by calling our own err_sys function.
It prints our error message along with a description of the system error that occurred
(e.g., "Protocol not supported" is one possible error from socket) and terminates the
process.		

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

/*
We fill in an Internet socket address structure (a sockaddr_in structure named
servaddr) with the server's IP address and port number. We set the entire structure
to 0 using bzero, set the address family to AF_INET, set the port number to 13 (which
is the well-known port of the daytime server on any TCP/IP host that supports this
service, as shown in Figure 2.18), and set the IP address to the value specified as the
first command-line argument (argv[1]). The IP address and port number fields in
this structure must be in specific formats: We call the library function htons ("host to
network short") to convert the binary port number, and we call the library function
inet_pton ("presentation to numeric") to convert the ASCII command-line argument
(such as 206.62.226.35 when we ran this example) into the proper format.
*/

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);


/*
The connect function, when applied to a TCP socket, establishes a TCP
connection with the server specified by the socket address structure pointed to by the
second argument. We must also specify the length of the socket address structure as
the third argument to connect, and for Internet socket address structures, we always
let the compiler calculate the length using C's sizeof operator
*/
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");

	exit(0);
}
