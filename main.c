#include <stdio.h>
#include "server.h"

extern int global_exit;

int main(void)
{
	server *s;

	printf("Starting server.\n");
	global_exit=0;

	s = server_new(4242);

	while(server_do(s))
		;

//printf("prool label 1\n");

	server_destroy(s);

printf("server exit\n");

	return 0;
}
