#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sqlite3.h>
#include<sys/stat.h>

#include "../pfa-src/db_manager.h"


void* init_DB(char* name_DB)
{
  char* cmd=NULL;
  struct stat s;
  sqlite3* db;
  int open;


  cmd=malloc(sizeof(char)*100);

  sprintf(cmd,"sqlite3 %s &",name_DB);

  if(stat(name_DB,&s) != 0)
    system(cmd);

  open = sqlite3_open(name_DB, &db);


  if (open==0)
    return db;

  free(cmd);

  return NULL;

}


int create_table(void* db,char* name_table, char* attributs,int (*callback)(void*,int,char**,char**))
{
  char* request=NULL;

  char* zErrMsg = "error: table was not create";
  int rc;

  request = malloc(strlen(name_table) * sizeof(char)  + strlen(attributs) * sizeof(char) + 100);

  sprintf(request,"CREATE TABLE  %s (%s);", name_table, attributs);

  rc = sqlite3_exec(db,request,callback, 0, &zErrMsg);
  if(rc != SQLITE_OK)
    {
      fprintf(stderr, "%s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 0;
    }

  free(request);


  return 42;

}


int write_DB(void* db, char* name_table, char* attributs, char* values, int (*callback)(void*,int,char**,char**))
{
  char* request=NULL;

  char* zErrMsg = "error: data was not insert into the DB";
  int rc;

  request = malloc(strlen(values) * sizeof(char) + strlen(name_table) *sizeof(char) + 100);

  sprintf(request,"INSERT INTO %s (%s) VALUES (%s);", name_table,attributs,values );


  rc = sqlite3_exec(db,request,callback, 0, &zErrMsg);
  if(rc != SQLITE_OK)
    {
      fprintf(stderr, "%s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }

  free(request);

  return rc;
}



int search_DB(void* db, char* name_table,char* attributs ,int (*callback)(void*,int,char**,char**))
{
  char* request;


  char* zErrMsg = "error: data was not find into the DB";
  int rc;


  request = malloc(strlen(attributs) + strlen(name_table)  + 100);

  sprintf(request,"SELECT %s FROM %s;", attributs,name_table);


  rc = sqlite3_exec(db,request,callback, 0, &zErrMsg);
  if(rc != SQLITE_OK)
    {
      fprintf(stderr, "%s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }
  free(request);

  return EXIT_SUCCESS;
}

int close_DB(void* db)
{
  if(sqlite3_close(db)==0)
    return 42;
  else
    return 0;

}

int delete_DB(char* name_DB)
{
  char* cmd=NULL;
  cmd=malloc(sizeof(char)*100);

  sprintf(cmd,"rm %s", name_DB);

  system(cmd);

  free(cmd);

  return 42;

}

