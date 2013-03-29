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
#define CHK(X) do { if(X == -1) {perror("Erreur systeme"); exit(1); } } while(0)

int sockfd = -1;
struct sockaddr bot_addr;
socklen_t bot_addrlen;
static int word_len(char * word)
{
	int l;
	for (l = 0; word[l] != '\0' && word[l] != ' ' && word[l] != '\n'; l++) ;
	return l;
}

static void open_socket (int port)
{
	struct sockaddr_in my_addr;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	CHK(sock);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons(port);
	my_addr.sin_family = AF_INET;
	int optval = 1;
	CHK(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval));

	CHK(bind(sock,(struct sockaddr *)&my_addr,sizeof(struct sockaddr_in)));
	CHK(listen(sock,1));
	sockfd = accept(sock,&bot_addr, &bot_addrlen);
	CHK(sockfd);
	close(sock);
	char msg[MAX_MSG_SIZE] ;
	recv(sockfd,msg,MAX_MSG_SIZE,0);
	int wlen = 4;
	if (strncmp(msg, "NAME", wlen) == 0) {
	  mm_botname(msg + wlen + 1,word_len(msg+wlen+1));	
	}
}

void bot_end_game()
{
	shutdown(sockfd,SHUT_RDWR);
	close(sockfd);
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
	int wlen = word_len(botdir);
	if      (strncmp(botdir, "NORTH"    ,wlen) == 0) {
		return 'k';
	}

	else if (strncmp(botdir, "NORTH_WEST",wlen) == 0) {
		return 'y';
	}

	else if (strncmp(botdir, "NORTH_EAST",wlen) == 0) {
		return 'u';
	}

	else if (strncmp(botdir, "SOUTH"     ,wlen) == 0) {
		return 'j';
	}

	else if (strncmp(botdir, "SOUTH_WEST",wlen) == 0) {
		return 'b';
	}

	else if (strncmp(botdir, "SOUTH_EAST",wlen) == 0) {
		return 'n';
	}

	else if (strncmp(botdir, "WEST"      ,wlen) == 0) {
		return 'h';
	}

	else if (strncmp(botdir, "EAST"      ,wlen) == 0) {
		return 'l';
	}
	else if (strncmp(botdir, "DOWN"      ,wlen) == 0) {
		return '>';
	}
	else if (strncmp(botdir, "UP"      ,wlen) == 0) {
		return '<';
	}
	fprintf(stderr,"Direction inconnue : %s\n",botdir);
	exit(1);

}

static void parse_botcmd(char * botcmd)
{
	int alen = word_len(botcmd);
	 if (strncmp(botcmd, "SEARCH", alen) == 0) {
		mm_keypress('s');
		return;
	}

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


void bot_turn(void)
{
	char msg[MAX_MSG_SIZE] ;
	char *map = get_map();
	if(sockfd == -1){
		open_socket(4242);
		snprintf(msg, MAX_MSG_SIZE, "START\nMAP_HEIGHT 22\nMAP_WIDTH 80\nSTART MAP\n%s\nEND MAP\nEND\n", map);
	}
	else {
		snprintf(msg, MAX_MSG_SIZE, "START\nSTART MAP\n%s\nEND MAP\nEND\n", map);
	}
	write_to_bot(msg);
	int msglen = recv(sockfd,msg,MAX_MSG_SIZE,0);
	parse_botcmd(msg);
}


