#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface_mm.h"
#include "../db_manager/db_manager.h"

extern void * db;

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
    char * table_name;
    table_name = malloc(MAX_CHAR * sizeof(char));

    char * args;
    args = malloc(MAX_CHAR * sizeof(char));

    // Tester les erreurs d'assignations dans les valeurs toujours utilisées
    if (d->id_party == INIT_VAR_INT)
    {
        printf("Error, id_party has not been assigned properly\n");
        return EXIT_FAILURE;
    }
    if (((d->date.day == INIT_VAR_INT) || (d->date.month == INIT_VAR_INT)) || (d->date.year == INIT_VAR_INT))
    {
        printf("Error, date has not been assigned properly\n");
        return EXIT_FAILURE;
    }
    if (d->mod.name == NULL)
    {
        printf("Error, mod informations have not been assigned properly\n");
        return EXIT_FAILURE;
    }
    if (d->bot.name == NULL)
    {
        printf("Error, bot informations have not been assigned properly\n");
        return EXIT_FAILURE;
    }

    get_table_name(table_name, d);

    if (strcmp(d->bot.name, "Explorer") == 0)
    {
        create_table(db, table_name, "DAY INT, MONTH INT, YEAR INT, DOORLVL INT, DOORDISC INT, STEPS INT", NULL);
        printf("\n\n%s\n\n", table_name);
        sprintf(args, "%d, %d, %d, %d, %d, %d", d->date.day, d->date.month, d->date.year, d->door_lvl, d->door_disc, d->steps);
        write_DB(db, table_name, "DAY, MONTH, YEAR, DOORLVL, DOORDISC, STEPS", args, NULL);
    }

    free(table_name);
    free(args);

return 0;

}

