#include"sqlite3.h"
#include"db_manager.h"
#include<stdio.h>
#include<stdlib.h>

int callback(void* NotUsed, int argc, char **argv, char **azColname)
{
  int i;
  for(i=0;i<argc;i++)
    {
      printf("%s = %s\n", azColname[i],argv[i] ? argv[i] : "NULL");
    }
  printf("\n");
  return 0;
}

void* test_creation_DB()
{
  sqlite3* db;
  
  db=init_DB("test.db");
  
  if(db!=NULL)
    printf("creation de la base de donnée: OK\n");
  else 
    printf("creation de la base de donnée: KO\n");      

  return db;
  
}

void test_creation_table(void* db)
{
  if(create_table(db,"test_table","test1 VARCHAR(20),test2 VARCHAR(20),test3 VARCHAR(20)",callback))
    printf("creation de la table: OK\n");
  else
    printf("creation de la table: KO\n");
}

void test_insertion(void* db)
{
  if(write_DB(db,"test_table","test1,test2,test3","'value1','value2','value3'",callback)==0)
    printf("insertion dans la table: OK\n");
  else
    printf("insertion dans la table: KO\n");
}

void test_selection(void* db)
{
  if(search_DB(db,"test_table","*", callback)==0)
    printf("selection dans la table: OK\n");
  else
    printf("selection dans la table: KO\n");
}

void test_fermeture(void* db)
{
  if(close_DB(db))
    printf("fermeture de la table: OK\n");
  else
    printf("fermeture de la table: KO\n");
}

void test_suppression(char* db)
{
  if(delete_DB(db))
    printf("suppression de la base de donnée: OK\n");
  else
    printf("suppression de la base de donnée: KO\n");
}

void main()
{
  printf("début du test\n");
  void* db;
  
  
  db=test_creation_DB();
  test_creation_table(db);
  test_insertion(db);
  test_selection(db);
  test_fermeture(db);
  test_suppression("test.db");
  
  printf("fin des tests");
  
}
