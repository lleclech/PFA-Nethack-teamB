#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bot_handler.h"

#define MAP_SIZE      1760 // 22*80
#define MAX_MSG_SIZE  2000 
#define MAX_CMD_SIZE  5

int sockfd;
struct sockaddr bot_addr
socklen_t bot_addrlen;

void open_socket (char *host, int port)
{
  struct sockaddr_un my_addr;
  int sock = socket(AF_UNIX, SOCK_STREAM, 0);
  if(sock == INVALID_SOCKET)
    {
      perror("socket()");
      exit(errno);
    } 
  my_addr.sin_addr = htonl(INADDR_ANY);
  my_addr.sin_port = htons(port);
  my_addr.sin_family = AF_UNIX;
  
  bind(sock,struct sockaddr *) &my_addr,sizeof(struct sockaddr_un));
  listen(sock,1);
  sockfd = accept(sock,&bot_addr, &bot_addr_size);
  close(sock);
}

int write_to_bot(char *msg)
{
  write(sockfd,msg,strlen(msg));
}

   static void
   send_init(void)
   {
   char msg[MAX_MSG_SIZE] = "";

   snprintf(msg, MAX_MSG_SIZE, "START\n
   MAP_HEIGHT 22\n
   MAP_WIDTH 80\n
   START MAP\n
   %s\n
   END MAP\n
   END\n", get_map());

// send msg on a socket to the bot
}

static void
send_map(void)
{
char msg[MAX_MSG_SIZE] = "";

snprintf(msg, MAX_MSG_SIZE, "START\n
START MAP\n
%s\n
END MAP\n
END\n", get_map());

// send msg on a socket to the bot
}

static void
get_map(void)
{

}

/* Give the size of the action keyword.
 * For exemple if botcmd is "MOVE SOUTH_WEST" then 4 is returned.
 */
	static int
action_len(char * botcmd)
{
	int l = 0;
	for (; botcmd[l] != '\0' && botcmd[l] != ' '; l++) ;

	return l;
}

/* Translate a direction in the bot format into a direction in Nethack format.
 * Return -1 if direction is invalid.
 */
	static int
botdir2nhdir(char * botdir)
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

	return -1;
}

/* Return a command understandable by Nethack's kernel.
 * The returned pointer should be freed afterwards.
 */
char *
botcmd_to_nhcmd(char * botcmd)
{
	int alen = action_len(botcmd);
	char * nhcmd = malloc(MAX_CMD_SIZE * sizeof(char));

	if (strncmp(botcmd, "MOVE", alen) == 0) {
		int c = botdir2nhdir(botcmd + alen + 1);
		if (c != -1) {
			snprintf(nhcmd, MAX_CMD_SIZE, "%c", (char)c);
		}
	}

	else if (strncmp(botcmd, "OPEN", alen) == 0) {
		int c = botdir2nhdir(botcmd + alen + 1);
		if (c != -1) {
			snprintf(nhcmd, MAX_CMD_SIZE, "o%c", (char)c);
		}
	}

	else if (strncmp(botcmd, "FORCE", alen) == 0) {
		int c = botdir2nhdir(botcmd + alen + 1);
		if (c != -1) {
			snprintf(nhcmd, MAX_CMD_SIZE, "\4%c", (char)c);
		}
	}

	else {
		snprintf(nhcmd, MAX_CMD_SIZE, "%s", botcmd);
	}

	/* default */
	return nhcmd;
}
