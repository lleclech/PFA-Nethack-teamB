#include "middle_man.h"
#include "interface_mm.h"
#include <string.h>
#include <assert.h>

#define MM_FIFO_LENGTH 100
#define MAX_TURNS 10000


char mm_map[81*21+1]; //(x y)
char mm_cmdbuf[MM_FIFO_LENGTH]; //FIFO containing bot commands 
int mm_turn = 0;
int mm_cmdtop = -1; //Command top pointer
int mm_cmdtail = -1; //Command tail pointer
struct window_procs realwindowprocs;

int mm_nb_sdoor = 0;
int mm_disc_sdoors = 0;


static void fifo_inc(int *i)
{
	(*i)++;
	*i=(*i)%MM_FIFO_LENGTH;
}

void middle_man_print_glyph(winid window,XCHAR_P x,XCHAR_P y,int glyph)
	/* Store the printed char in the structure before display */
{
	int ch,color;
	unsigned special;
	mapglyph(glyph,&ch,&color,&special,x,y);
	assert(ch < 256);
	if((ch == '|' || ch == '-') 
			&& mm_map[x+81*y] == '+')
	/* Allows simpler opening door logic on bot side */
		mm_map[x+81*y] = '#';
	else
		mm_map[x+81*y]=(char)ch;
	realwindowprocs.win_print_glyph(window,x,y,glyph);
}

int middle_man_nh_poskey(int *x, int *y, int *mod){
	int key;
	if(mm_cmdtop == mm_cmdtail){
		/* Game is asking for a keypress that the bot didn't give */
		if (mm_turn > MAX_TURNS){
			exit_nhwindows(NULL);
			bot_end_game();
			void * db = init_db("Netbot_highscores");
			char * table_name = malloc(100*sizeof(char)); // Name of the table where datas "d" are to be stored
			struct AllData *d = init_AllData();
			assign_mod(d ,"SEARCH_DOORS", 1);
			assign_bot(d ,"RANDOM_VALUES", 1);
			assign_nb_door_level(d, mm_nb_sdoor); 
			assign_nb_steps(d, MAX_TURNS);
			assign_nb_door_discovered(d, mm_disc_sdoors);

			write_into_database(d);
			get_table_name(table_name, d); // Get right name of the table
			printf("Discovered secret doors: %d / %d\n",mm_disc_sdoors, mm_nb_sdoor );
			printf("Stats on database\n");
			printf("Generated secret doors :\n");
			printf("Mean : %d\n", get_mean_on_table(db, table_name, "DOORLVL"));
			printf("Median : %d\n", get_median_on_table(db, table_name, "DOORLVL"));
			printf("Standard Deviation : %d\n", get_std_deviation_on_table(db, table_name, "DOORLVL"));
			printf("Discoverd secret doors :\n");
			printf("Mean : %d\n", get_mean_on_table(db, table_name, "DOORDISC"));
			printf("Median : %d\n", get_median_on_table(db, table_name, "DOORDISC"));
			printf("Standard Deviation : %d\n", get_std_deviation_on_table(db, table_name, "DOORDISC"));
			printf("Steps :\n");
			printf("Mean : %d\n", get_mean_on_table(db, table_name, "STEPS"));
			printf("Median : %d\n", get_median_on_table(db, table_name, "STEPS"));
			printf("Standard Deviation : %d\n", get_std_deviation_on_table(db, table_name, "STEPS"));
			destroy_AllData(d);
			terminate(EXIT_SUCCESS);
		}
		else {
			bot_turn();
			mm_turn++;
		}
	}
	key = mm_cmdbuf[mm_cmdtail]; 
	fifo_inc(&mm_cmdtail);
	*mod = 0;
	return key;

}

void install_middle_man(struct window_procs * windowprocs){
	/* Initialise map, and change glyph printing logic */
	int i;
	memcpy(&realwindowprocs,windowprocs,sizeof realwindowprocs);
	memset(mm_map,' ',81*21);
	for (i = 1; i <= 21; i++){
		mm_map[81*i] = '\r';
	}
	mm_map[81*21] = '\0';
	mm_cmdtop = 1;
	mm_cmdbuf[0] = 'y';
	mm_cmdtail = 0;
	windowprocs->win_print_glyph = middle_man_print_glyph;
	windowprocs->win_nh_poskey = middle_man_nh_poskey;
}

char *get_map(){
	/* Simply get the map */
	return mm_map;
}


void mm_keypress(char c){
	mm_cmdbuf[mm_cmdtop] = c;		
	fifo_inc(&mm_cmdtop);
}
