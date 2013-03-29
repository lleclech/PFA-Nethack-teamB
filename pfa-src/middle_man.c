#include "middle_man.h"
#include "bot_handler.h"
#include "interface_mm.h"
#include "math_tool.h"
#include <string.h>
#include <assert.h>
#include <sqlite3.h>

#define MM_FIFO_LENGTH 100
#define MAX_TURNS 10000


char mm_map[81*21+1]; //(x y)
char mm_cmdbuf[MM_FIFO_LENGTH]; //FIFO containing bot commands 
char *bot_name = NULL;
int mm_turn = 0;
int mm_cmdtop = -1; //Command top pointer
int mm_cmdtail = -1; //Command tail pointer
struct window_procs realwindowprocs;

struct List_Nbrs * MATH_LIST;
int mm_nb_sdoor = 0;
int mm_disc_sdoors = 0;
int mm_depth = 1;

static void fifo_inc(int *i)
{
	(*i)++;
	*i=(*i)%MM_FIFO_LENGTH;
}

void mm_botname(char *name, int name_len){
	if(bot_name) 
		free(bot_name);
	bot_name = strndup(name,name_len);
}

void middle_man_print_glyph(winid window,XCHAR_P x,XCHAR_P y,int glyph)
	/* Store the printed char in the structure before display */
{
	int ch,color;
	unsigned special;
	mapglyph(glyph,&ch,&color,&special,x,y);
	if (depth(&u.uz) != mm_depth){
		mm_reset_map();
		mm_depth = depth(&u.uz);
	}
	assert(ch < 256);
	if((ch == '|' || ch == '-') 
			&& mm_map[x+81*y] == '+')
	/* Allows simpler opening door logic on bot side */
		mm_map[x+81*y] = '#';
	else if (ch != ' ')
		mm_map[x+81*y]=(char)ch;
	realwindowprocs.win_print_glyph(window,x,y,glyph);
}

int get_id_party(void)
{
  int id_party;
  char buffer[10] = "";
  FILE * f_id_party = fopen("../../id_party.txt", "r+");

  if (f_id_party == NULL)
    {
      f_id_party = fopen("../../id_party.txt", "w+");
      fprintf(f_id_party, "1");
      fclose(f_id_party);
      return 0;
    }

  fgets(buffer, 10, f_id_party);
  id_party = atoi(buffer);
  fclose(f_id_party);
  fopen("../../id_party.txt", "w+");

  fprintf(f_id_party, "%d", id_party + 1);

  fclose(f_id_party);

  return id_party;
}

int middle_man_nh_poskey(int *x, int *y, int *mod){
	int key;
	if(mm_cmdtop == mm_cmdtail){
		/* Game is asking for a keypress that the bot didn't give */
		if (mm_turn > MAX_TURNS){
			exit_nhwindows(NULL);
			bot_end_game();
			FILE * f = fopen("stats.txt", "w+");
			fprintf(f,"%d %d %d\n",mm_disc_sdoors, mm_nb_sdoor,mm_depth );
			fflush(f);
			fclose(f);

			MATH_LIST = create_list_nbrs();
			void * db = init_DB("../../Netbot_highscores");
			char * table_name = malloc(100*sizeof(char)); // Name of the table where datas "d" are to be stored
			struct AllData * d = init_AllData();
			d->id_party = get_id_party();
			printf("ID_PARTY = %d\n", d->id_party);
			assign_mod(d ,"Exploration", 0);
			if(bot_name){
				assign_bot(d ,bot_name, 1);
			}
			else
				assign_bot(d ,"No_name", 1);
			assign_nb_door_level(d, mm_nb_sdoor); 
			printf("DOORS_GENERATED = %d\n", mm_nb_sdoor);
			assign_nb_door_discovered(d, mm_disc_sdoors);
			printf("DOORS_DISCOVERED = %d\n", mm_disc_sdoors);
			d->depth = mm_depth;
			printf("DEPTH_REACHED = %d\n", mm_depth);

			write_into_database(d);
			get_table_name(table_name, d); // Get right name of the table
			printf("Stats on database\n");
			printf("Generated secret doors :\n");
			printf("Mean : %d\n", get_mean_on_table(db, table_name, "DOORLVL"));
			printf("Median : %d\n", get_median_on_table(db, table_name, "DOORLVL"));
			printf("Standard Deviation : %d\n", get_std_deviation_on_table(db, table_name, "DOORLVL"));
			printf("Discoverd secret doors :\n");
			printf("Mean : %d\n", get_mean_on_table(db, table_name, "DOORDISC"));
			printf("Median : %d\n", get_median_on_table(db, table_name, "DOORDISC"));
			printf("Standard Deviation : %d\n", get_std_deviation_on_table(db, table_name, "DOORDISC"));
			printf("Depth :\n");
			printf("Mean : %d\n", get_mean_on_table(db, table_name, "DEPTH"));
			printf("Median : %d\n", get_median_on_table(db, table_name, "DEPTH"));
			printf("Standard Deviation : %d\n", get_std_deviation_on_table(db, table_name, "DEPTH"));
			if (bot_name)
			  free(bot_name);
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
	*x = 0;
	*y = 0;
	return key;
}

void mm_reset_map(){
	int i;
	memset(mm_map,' ',81*21);
	for (i = 1; i <= 21; i++){
		mm_map[81*i] = '\r';
	}
	mm_map[81*21] = '\0';
}

void install_middle_man(struct window_procs * windowprocs){
	/* Initialise map, and change glyph printing logic */
	memcpy(&realwindowprocs,windowprocs,sizeof realwindowprocs);
	mm_reset_map();
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
