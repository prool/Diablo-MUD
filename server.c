#include <stdlib.h>
#include <unistd.h>
#include "socket.h"
#include "client.h"
#include "server.h"

struct server{
	int socket;
	int maxfd;
	fd_set readfds;
	client *clients;
};

server *server_new(int port)
{
	server *s;
	s = malloc(sizeof(server));

	s->socket = socket_listen_new(port);
	s->maxfd = s->socket;
	FD_ZERO(&s->readfds);
	FD_SET(s->socket, &s->readfds);

	return s;
}

int server_do(server *s)
{
	fd_set readfds;
/*	client *c;*/

	readfds = s->readfds;

	select(s->maxfd + 1, &readfds, NULL, NULL, NULL);

	if(FD_ISSET(s->socket, &readfds))
	{
		client_new(&s->clients, s->socket);
	}

	return 1;
}

void server_destroy(server *s)
{
	socket_close(s->socket);
	free(s);
}
