#ifndef DATABASE
#define DATABASE

void* init_DB(char* name_DB);

int create_table(void* db,char* name_table, char* attributs,int (*callback)(void*,int,char**,char**));

/*crée une table dont les attributs sont contenus dans un char *.
  L'attirbuts doit être accompagné de du type de variable, un attributs aura
  donc la forme "Nom_de_colonne Type_de_donnée".*/

int write_DB(void* db, char* name_table, char*attributs, char* values,int (*callback)(void*,int,char**,char**));
//permet d'écrire dans une table (équivalent à un INSERT INTO).

int search_DB(void* db, char* name_table, char* attributs,int (*callback)(void*,int,char**,char**));
/*permet récuperer des informations
  dans une table (équivalent à un SELECT);*/

int close_DB(void* db);
// ferme la base de donnée.

int delete_DB(char* name_DB);
// supprime une base donnée.

#endif


