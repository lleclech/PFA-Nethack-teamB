#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../pfa-src/interface_mm.h"
#include "../pfa-src/db_manager.h"

struct AllData * init_AllData(void)
{
  struct AllData * d;
  d = malloc(sizeof(struct AllData));

  d->id_party = INIT_VAR_INT;
  d->mod.name = NULL;

  d->bot.id = INIT_VAR_INT;
  d->bot.name = NULL;

  d->date.day = INIT_VAR_INT;
  d->date.month = INIT_VAR_INT;
  d->date.year = INIT_VAR_INT;

  d->door_lvl = INIT_VAR_INT;
  d->door_disc = INIT_VAR_INT;
  d->steps = INIT_VAR_INT;

  return d;
}

void assign_id_party(struct AllData * d, const int id)
{
  d->id_party = id;
}

void assign_mod(struct AllData * d, const char * name, const int id )
{
  d->mod.id = id;

  d->mod.name = malloc((strlen(name) + 1) * sizeof(char));
  strcpy(d->mod.name, name);
}

void assign_bot(struct AllData * d, const char * name, const int id)
{
  d->bot.id = id;

  d->bot.name = malloc((strlen(name) + 1) * sizeof(char));
  strcpy(d->bot.name, name);
}

void assign_date(struct AllData * d, const struct Date dt)
{
  d->date.day = dt.day;
  d->date.month = dt.month;
  d->date.year = dt.year;
}

void assign_nb_steps(struct AllData * d, const int nb)
{
  d->steps = nb;
}

void assign_nb_door_discovered(struct AllData * d, const int nb)
{
  d->door_disc = nb;
}

void assign_nb_door_level(struct AllData * d, const int nb)
{
  d->door_lvl = nb;
}

void assign_nb_monsters_generated(struct AllData * d, const int nb)
{
  d->steps = nb;
}

void assign_nb_monsters_killed(struct AllData * d, const int nb)
{
  d->steps = nb;
}

int destroy_AllData(struct AllData * d)
{
  if (d == NULL)
    {
      printf("Erreur, le pointeur passé en argument n'est pas assigné\n");
      return EXIT_FAILURE;
    }
  else
    {
      if (d->mod.name == NULL)
	{
	  printf("Erreur, le champ mod_name n'est pas assigné\n");
	  return EXIT_FAILURE;
	}
      if (d->bot.name == NULL)
	{
	  printf("Erreur, le champ bot_name n'est pas assigné\n");
	  return EXIT_FAILURE;
	}
      else
	{
	  free(d->mod.name);
	  free(d->bot.name);
	}
      free(d);
    }
  return EXIT_SUCCESS;
}

/*
 *  Given a structure "All Data", write the name of the table where it has to be stored
 */
int get_table_name(char * buffer, struct AllData * d)
{
    sprintf(buffer, "table_bot_%s_%d_mod_%s_%d", d->bot.name, d->bot.id, d->mod.name, d->mod.id);
    return EXIT_SUCCESS;
}

// A compléter avec les fonctions de gestion de la bd de Louis L
int write_into_database(struct AllData * d)
{
  FILE * log = fopen("log_pfa.txt", "w+");
  fprintf(log, "debug 0\n"); fflush(log);
  char * table_name;
    table_name = malloc(MAX_CHAR * sizeof(char));

  fprintf(log, "debug 1\n"); fflush(log);

    char * args;
    args = malloc(MAX_CHAR * sizeof(char));

  fprintf(log, "debug 2\n"); fflush(log);

    time_t timestamp;
    struct tm * t;
    timestamp = time(NULL);
    t = localtime(&timestamp);

  fprintf(log, "debug 3\n"); fflush(log);

    d->date.year = t->tm_year + 1900;
    d->date.month = t->tm_mon;
    d->date.day = t->tm_mday;

    fprintf(log, "debug 4\n"); fflush(log);

    // Tester les erreurs d'assignations dans les valeurs toujours utilisées
    if (d->id_party == INIT_VAR_INT)
    {
      fprintf(log, "Error, id_party has not been assigned properly\n");
      return EXIT_FAILURE;
    }
    fprintf(log, "debug 4.1\n"); fflush(log);
    if (d->mod.name == NULL)
    {
      fprintf(log, "Error, mod informations have not been assigned properly\n");
        return EXIT_FAILURE;
    }
    fprintf(log, "debug 4.2\n"); fflush(log);
    if (d->bot.name == NULL)
    {
      fprintf(log, "Error, bot informations have not been assigned properly\n");
        return EXIT_FAILURE;
    }

    fprintf(log, "debug5\n"); fflush(log);

    get_table_name(table_name, d);

    if (strcmp(d->bot.name, "Explorer") == 0)
    {
      fprintf(log, "debug6\n"); fflush(log);
      void *db = init_DB("Netbot_highscores");
      create_table(db, table_name, "DAY INT, MONTH INT, YEAR INT, DOORLVL INT, DOORDISC INT, STEPS INT", NULL);
      sprintf(args, "%d, %d, %d, %d, %d, %d", d->date.day, d->date.month, d->date.year, d->door_lvl, d->door_disc, d->steps);
      write_DB(db, table_name, "DAY, MONTH, YEAR, DOORLVL, DOORDISC, STEPS", args, NULL);
    }
    else
    {
        printf("Non-recognized bot name\n");
    }

    free(table_name);
    free(args);

return 0;

}

