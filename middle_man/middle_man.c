#include "middle_man.h"
#include <string.h>

#define MM_FIFO_LENGTH 100

int mm_map[80][21]; //(x y)
int mm_cmdbuf[MM_FIFO_LENGTH]; //FIFO containing bot commands 
int mm_cmdtop = -1; //Command top pointer
int mm_cmdtail = -1; //Command tail pointer
struct window_procs realwindowprocs;

static void fifo_inc(int *i)
{
	*i++;
	*i=(*i)%MM_FIFO_LENGTH;
}

void middle_man_print_glyph(winid window,xchar x,xchar y,int glyph)
/* Store the printed char in the structure before display */
{
  int ch,color;
  unsigned special;
  mapglyph(glyph,&ch,&color,&special,x,y);
  mm_map[x][y]=ch;
  realwindowprocs.win_print_glyph(window,x,y,glyph);
}

int middle_man_nh_poskey(int *x, int *y, int *mod){
	int key;
	assert(mm_cmdtop != mm_cmdtail);
	/* Game is asking for a keypress that the bot didn't give */
	key = mm_cmdbuf[mm_cmdtail]; 
	fifo_inc(&mm_cmdtail);
	*mod = mm_cmdbuf[mm_cmdtail]; 
	fifo_inc(&mm_cmdtail);
	return key;
}

struct window_procs * install_middle_man(struct window_procs * windowprocs){
/* Initialise map, and change glyph printing logic */
	int i,j;
	memcpy(&realwindowprocs,windowprocs,sizeof realwindowprocs);
	for (i = 0; i < 80; i++){
		for (j = 0; j < 21; j++){
			mm_map[i][j] = ' ';
		}
	}
	mm_cmdtop = 0;
	mm_cmdtail = 0;
	windowprocs->win_print_glyph = middle_man_print_glyph;
	windowprocs->win_nh_poskey = middle_man_nh_poskey;
	return windowprocs;
}

int get_glyph(int x,int y){
/* Simply get the char */
	assert(x < 80 && x >= 0);
	assert(y < 21 && y >= 0);
	return mm_map[x][y];
}


void simulate_keypress(int key, int mod){
	mm_cmdbuf[mm_cmdtop] = key;		
	fifo_inc(&mm_cmdtop);
	mm_cmdbuf[mm_cmdtop] = mod;	
	fifo_inc(&mm_cmdtop);
}
