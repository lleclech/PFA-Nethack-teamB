// Toutes les variables enregistrables entières seront initialisées à -1
#define INIT_VAR_INT -1

/* ---
Name_mod disponibles
// ---
SEARCH_DOORS
KILL_MONSTERS
   --- */

struct Date
{
  int day;
  int month;
  int year;
};

/*
 * Informations sur le mod utilisé
 */
struct Mod_Info
{
  int id;
  char * name;
};

/*
 * Informations sur le bot utilisé
 */
struct Bot_Info
{
  int id;
  char * name;
};

/* 
 * La structure AllData contient toutes les données récupérables par le bot
 * Les variables sont toutes initialisées à une valeur qui ne peut pas être renvoyée par le middle-man dans les conditions normales (-1, NULL,...)
 * On sait ainsi quelle valeur ont été renvoyées par le middle-man après l'execution du bot
 */
struct AllData
{
  int id_party;
  struct Mod_Info mod;       // Informations sur le mod utilisé
  struct Bot_Info bot;       // Informations sur le bot utilisé
  struct Date date;
  int nb_door_level;         // Nombre total de portes dans le niveau généré
  int nb_door_discovered;    // Nombre de portes découvertes
  int nb_steps;              // Nombre de pas effectués
  int nb_monsters_generated; // Nombre de monstres générés
  int nb_monsters_killed;    // Nombre de monstres tués
};

/*
 * Initialisation de la structure à des valeurs non-r
 */
struct AllData * init_AllData(void);

/*
 * Ecriture de l'identifiant de la partie (entier) dans la structure de données
 */
void assign_id_party(struct AllData *, const int);

/*
 * Ecriture du nom et id du mod utilisé pour la partie (chaine de char) dans la structure de données
 */
void assign_mod(struct AllData *, const char *, const int);

/*
 * Ecriture du nom et id du bot utilisé pour la partie (chaine de char) dans la structure de données
 */
void assign_bot(struct AllData *, const char *, const int);

/*
 * Ecriture de la date de la partie (struct Date) dans la structure de données
 */
void assign_date(struct AllData *, const struct Date);

/*
 * Ecriture du nombre de portes découvrables pendant la partie (entier) dans la structure de données
 */
void assign_nb_door_level(struct AllData *, const int);

/*
 * Ecriture du nombre de portes découvertes pendant la partie (entier) dans la structure de données
 */
void assign_nb_door_discovered(struct AllData *, const int);

/*
 * Ecriture du nombre de pas effectués pendant la partie (entier) dans la structure de données
 */
void assign_nb_steps(struct AllData *, const int);

/*
 * Ecriture du nombre de monstres générés pendant la partie (entier) dans la structure de données
 */
void assign_nb_monsters_generated(struct AllData *, const int);

/*
 * Ecriture du nombre de monstres tués pendant la partie (entier) dans la structure de données
 */
void assign_nb_monsters_killed(struct AllData *, const int);

/*
 * Destruction de la structure créée
 */
int destroy_AllData(struct AllData *);

/*
 * Insertion des données stockées dans la base de données
 */
int write_into_database(struct AllData *);
