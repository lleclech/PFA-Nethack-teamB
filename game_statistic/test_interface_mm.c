#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface_mm.h"

int NO_PARTY = 0; // Sert à incrémenter le n° des parties jouées pour les test

/*
NOTE, 22/12/12, Sven : Sert à générer des valeurs aléatoires, à modifier légèrement car incompatible avec la structure...
 */
void make_AllData_SD(struct AllData * d)
{
  int i = 0;
  assign_id_party(d, NO_PARTY);
  NO_PARTY++;

  assign_mod(d ,"SEARCH_DOORS", 1);
  assign_bot(d ,"RANDOM_VALUES", 1);

  i = ((rand() % (100 - 10 + 1)) + 10);
  assign_nb_door_level(d, i); 

  i = ((rand() % (d->nb_door_level - 0 + 1)) + 0);
  assign_nb_door_discovered(d, i);

  i = ((rand() % (1000000 - d->nb_door_discovered + 1)) + d->nb_door_discovered);
  assign_nb_steps(d, i); 
}

/*
NOTE, 22/12/12, Sven : Sert à afficher les valeurs de la structure, à modifier légèrement car incompatible avec la structure...
 */
void display_AllData(struct AllData * d)
{
  printf("Party n°%d\n", d->id_party);
  printf("Mod : id = %d, name = %s\n", d->mod.id, d->mod.name);
  printf("Bot : id = %d, name = %s\n", d->bot.id, d->bot.name);

  if (d->nb_door_level != INIT_VAR_INT)
    {
      printf("%d doors could have been discovered\n", d->nb_door_level);
    }  
  if (d->nb_door_discovered != INIT_VAR_INT)
    {
      printf("%d doors have been discovered\n", d->nb_door_discovered);
    }
  if (d->nb_steps != INIT_VAR_INT)
    {
      printf("Bot made %d steps across the level\n", d->nb_steps);
    }
  if (d->nb_monsters_generated != INIT_VAR_INT)
    {
      printf("%d monsters were generated\n", d->nb_monsters_generated);
    }
  if (d->nb_monsters_killed != INIT_VAR_INT)
    {
      printf("Bot killed %d monsters during this session\n", d->nb_monsters_killed);
    }
}

/*
NOTE, 22/12/12, Sven : Pour les test, à modifier et déplacer
 */
int main(int argc, char **argv)
{
  srand(time(NULL));  

  struct AllData * d;
  char done = 1;

  while (done != '0')
    {
      d = init_AllData();
      make_AllData_SD(d);
      display_AllData(d);
      destroy_AllData(d);
      printf("Press 0 then Enter to quit - ");
      done = getchar();
    }

  return EXIT_SUCCESS;
}
