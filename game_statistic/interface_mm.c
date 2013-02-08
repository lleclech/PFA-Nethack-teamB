#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface_mm.h"


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

  d->nb_door_level = INIT_VAR_INT;
  d->nb_door_discovered = INIT_VAR_INT;
  d->nb_steps = INIT_VAR_INT;
  d->nb_monsters_generated = INIT_VAR_INT;
  d->nb_monsters_killed = INIT_VAR_INT;

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

void assign_nb_door_level(struct AllData * d, const int nb)
{
  d->nb_door_level = nb;
}

void assign_nb_door_discovered(struct AllData * d, const int nb)
{
  d->nb_door_discovered = nb;
}

void assign_nb_steps(struct AllData * d, const int nb)
{
  d->nb_steps = nb;
}

void assign_nb_monsters_generated(struct AllData * d, const int nb)
{
  d->nb_steps = nb;
}

void assign_nb_monsters_killed(struct AllData * d, const int nb)
{
  d->nb_steps = nb;
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

// A compléter avec les fonctions de gestion de la bd de Louis L
int write_into_database(struct AllData * d) // Rajouter en argument la base de données et le callback ?
{
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
      printf("Error while writing mod_name\n");
      return EXIT_FAILURE;
    }
  if (d->bot.name == NULL)
    {
      printf("Error while writing bot_name\n");
      return EXIT_FAILURE;
    }
    
  // Rentrer les valeurs utilisées dans la base de données
  /*
    NOTE, 22/12/12, Sven : A compléter, utilisation des fonctions de Louis principalement...
  if ()
    {
     
    }
  */
  
}

