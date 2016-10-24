#include <string.h>
#include <stdio.h> // prool
#include <stdlib.h> // prool
#include "parse.h"
#include "client.h"
#include "buffer.h"
#include "character.h"
#include "table.h"

extern int global_exit;

static table *commands;

struct command {
	const char *name;
	void (*func)(client *);
};

static void look(struct client *c)
{
	room_look(c);
}

void help (struct client *c) // prool
{
cprintf(c,"Commands:\n\
Original:\n\
look - look\n\
whoami - who am i\n\
Prool's command:\n\
prool, prool2 - debug commands\n\
shutdown - shutdown server\n\
help - this help\n");
}

void prool (struct client *c) // prool
{
printf("prool пруль\n");
cprintf(c, "prool пруль\n");
}

void prool2 (struct client *c) // prool
{
printf("prool2\n");
cprintf(c, "prool2 UTF-8 пруль!\n");
}

void quit (struct client *c) // prool
{
printf("quit\n");
cprintf(c, "no Quit!!!\n");
}

void shutdown (struct client *c) // prool
{
printf("shutdown\n");
cprintf(c, "shutdown!!!\n");
global_exit=1;
}

static void whoami(struct client *c)
{
	struct character *ch;

	ch = client_character(c);
	cprintf(c, "You are %s.\r\n", character_username(ch));
	cprintf(c, "You are currently located at: '%s'\r\n",
		character_room_name(ch));
}

static struct command command_list[] = 
{
	{"whoami", 	whoami},
	{"look", 	look},
	{"prool",	prool},
	{"quit",	quit},
	{"shutdown",	shutdown},
	{"help",	help},
	{"пруль",	prool2},
	{NULL,		NULL}
};

void parser_init(void)
{
	int i = 0;

	commands = table_new();

	while(1)
	{
		const char *name;
		void (*func)(client *);

		name = command_list[i].name;
		func = command_list[i].func;
		
		if(!name)
			break;

		table_add(commands, name, func);
		i++;
	}
}


void parse_command(struct client *c)
{
	const char *msg = client_buffer(c);
	void (*func)(client *);

	func = table_get(commands, msg);
	if(func)
	{
		func(c);
	} else {
		cprintf(c, "\r\nWhat?\r\n");
	}
}
