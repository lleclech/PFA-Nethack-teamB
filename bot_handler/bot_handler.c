#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include "bot_handler.h"
#include "middle_man.h"

#define MAP_SIZE      1760 // 22*80
#define MAX_MSG_SIZE  2000 
#define MAX_CMD_SIZE  5

int sockfd = -1;
struct sockaddr bot_addr;
socklen_t bot_addrlen;

void open_socket (int port)
{
	struct sockaddr_in my_addr;
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sock == -1)
	{
		perror("socket()");
		exit(errno);
	} 
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(port);
	my_addr.sin_family = AF_INET;

	bind(sock,(struct sockaddr *) &my_addr,sizeof(struct sockaddr_in));
	listen(sock,1);
	sockfd = accept(sock,&bot_addr, &bot_addrlen);
	close(sock);
}

static int write_to_bot(char *msg)
{
	return write(sockfd,msg,strlen(msg));
}

/* Translate a direction in the bot format into a direction in Nethack format.
 * Return -1 if direction is invalid.
 */
static int botdir2nhdir(char * botdir)
{
	if      (strcmp(botdir, "NORTH"     ) == 0) {
		return 'k';
	}

	else if (strcmp(botdir, "NORTH_WEST") == 0) {
		return 'y';
	}

	else if (strcmp(botdir, "NORTH_EAST") == 0) {
		return 'u';
	}

	else if (strcmp(botdir, "SOUTH"     ) == 0) {
		return 'j';
	}

	else if (strcmp(botdir, "SOUTH_WEST") == 0) {
		return 'b';
	}

	else if (strcmp(botdir, "SOUTH_EAST") == 0) {
		return 'n';
	}

	else if (strcmp(botdir, "WEST"      ) == 0) {
		return 'h';
	}

	else if (strcmp(botdir, "EAST"      ) == 0) {
		return 'l';
	}
	fprintf(stderr,"Direction inconnue : %s\n",botdir);
	exit(1);

}

/* Give the size of the action keyword.
 * For exemple if botcmd is "MOVE SOUTH_WEST" then 4 is returned.
 */
static int word_len(char * word)
{
	int l;
	for (l = 0; word[l] != '\0' && word[l] != ' ' && word[l] != '\n'; l++) ;
	return l;
}

static void parse_botcmd(char * botcmd)
{
	int alen = word_len(botcmd);

	if (strncmp(botcmd, "OPEN", alen) == 0) {
		mm_keypress('o');
	}
	else if (strncmp(botcmd, "FORCE", alen) == 0) {
		mm_keypress('\4');
	}
	else if (strncmp(botcmd, "MOVE", alen) == 0) {
	}
	else{
		fprintf(stderr,"Commande inconnue : %s\n",botcmd);
		exit(1);
	}
	botcmd += alen + 1;
	mm_keypress(botdir2nhdir(botcmd));
}

void read_bot_orders()
{
	char msg[MAX_MSG_SIZE];
	recv(sockfd,msg,MAX_MSG_SIZE,0);
	parse_botcmd(msg);
}	


 void send_init(void)
{
	char msg[MAX_MSG_SIZE];
	char *map = get_map();
	snprintf(msg, MAX_MSG_SIZE, "START\nMAP_HEIGHT 22\nMAP_WIDTH 80\nSTART MAP\n%s\nEND MAP\nEND\n", map);
	write_to_bot(msg);
}

void send_map(void)
{
	char msg[MAX_MSG_SIZE] ;
	char *map = get_map();
	snprintf(msg, MAX_MSG_SIZE, "START\nSTART MAP\n%s\nEND MAP\nEND\n", map);
	write_to_bot(msg);
}


