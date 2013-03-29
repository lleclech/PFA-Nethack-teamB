#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sqlite3.h>

#include "str.h"
#include "axis.h"
#include "highchart.h"
#include "html.h"
#include "macros.h"

struct Data
{
  int day;
  int month;
  int year;
  int doorlvl;
  int doordisc;
  int steps;
};

static int nTable;
static char** tablenames;

static int* nData;
static struct Data** datas;
static struct Data* currentData;

void usage(const char* s)
{
  fprintf(stderr, "%s <database file name> <output html file name>\n", s);
  exit(EXIT_FAILURE);
}

static int getNTable(void* nt, int argc, char** argv, char** azColName) {
  (void)argc;
  (void)azColName;
  *(int*)nt = atoi(argv[0]);
  return 0;
}

static int getTables(void* ind, int argc, char** argv, char **azColName) {
  (void)argc;
  (void)azColName;

  int* i = (int*)ind;
  tablenames[*i] = str__dup(argv[0]);
  *i += 1;
  return 0;
}

static int getNData(void* nd, int argc, char** argv, char** azColName) {
  (void)argc;
  (void)azColName;
  *(int*)nd = atoi(argv[0]);
  return 0;
}

static int getDatas(void* ind, int argc, char** argv, char **azColName) {

  struct Data* d = currentData + *(int*)ind;
  *(int*)ind += 1;

  int i = 0;
  for(; i < argc; ++i)
  {
    if(argv[i])
    {
      if(strcmp(azColName[i], "DAY") == 0)
        d->day = atoi(argv[i]);
      else if(strcmp(azColName[i], "MONTH") == 0)
        d->month = atoi(argv[i]);
      else if(strcmp(azColName[i], "YEAR") == 0)
        d->year = atoi(argv[i]);
      else if(strcmp(azColName[i], "DOORLVL") == 0)
        d->doorlvl = atoi(argv[i]);
      else if(strcmp(azColName[i], "DOORDISC") == 0)
        d->doordisc = atoi(argv[i]);
      else if(strcmp(azColName[i], "STEPS") == 0)
        d->steps = atoi(argv[i]);
    }
  }

  return 0;
}

int main(int argc, char** argv)
{
  if(argc != 3)
    usage(argv[0]);

  char buffer[1024];
  char* zErrMsg = 0;
  int i, j, k, rc;
  
  // open database
  sqlite3 *db;
  rc = sqlite3_open(argv[1], &db);
  if(rc)
  {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(EXIT_FAILURE);
  }

  // get ntable
  rc = sqlite3_exec(db, "select count(*) from sqlite_master where type='table'", getNTable, (void*)&nTable, &zErrMsg);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "Unable to get number of tables\n");
    sqlite3_free(zErrMsg);
    sqlite3_close(db);
    exit(EXIT_FAILURE);
  }

  if(nTable > 0)
  {
    // get tables
    tablenames = STAT_MALLOC(char*, nTable);
    nData = STAT_MALLOC(int, nTable);
    datas = STAT_MALLOC(struct Data*, nTable);

    for(i = 0; i < nTable; ++i)
    {
      tablenames[i] = NULL;
      datas[i] = NULL;
    }

    i = 0;
    rc = sqlite3_exec(db, "select name from sqlite_master where type='table' order by name", getTables, (void*)&i, &zErrMsg);
    if(rc != SQLITE_OK) {
      fprintf(stderr, "Unable to get the tables\n");
      sqlite3_free(zErrMsg);
      sqlite3_close(db);
      exit(EXIT_FAILURE);
    }

    // get all datas
    fprintf(stderr, "%d tables:\n", nTable);
    i = 0;
    while(i < nTable)
    {
      fprintf(stderr, "\t%s\n", tablenames[i]);

      // get number of datas
      sprintf(buffer, "select count(*) from %s", tablenames[i]);
      rc = sqlite3_exec(db, buffer, getNData, nData + i, &zErrMsg);
      if(rc != SQLITE_OK)
      {
        fprintf(stderr, "Unable to get the number of datas in table %s\n", tablenames[i]);
        sqlite3_free(zErrMsg);
        SAFE_FREE(tablenames[i]);
        tablenames[i] = tablenames[nTable - 1];
        --nTable;
      }
      else
      {
        fprintf(stderr, "\t\t%d datas\n", nData[i]);
        datas[i] = STAT_MALLOC(struct Data, nData[i]);

        // get datas
        currentData = datas[i];
        j = 0;
        sprintf(buffer, "select * from %s", tablenames[i]);
        rc = sqlite3_exec(db, buffer, getDatas, &j, &zErrMsg);
        if(rc != SQLITE_OK)
        {
          fprintf(stderr, "Unable to get the data in table %s\n", tablenames[i]);
          sqlite3_free(zErrMsg);
          SAFE_FREE(datas[i]);
          SAFE_FREE(tablenames[i]);
          tablenames[i] = tablenames[nTable - 1];
          --nTable;
        }
        else
        {
          ++i;
        }
      }
    }

    // generate the charts
    int nChart = nTable + 1;

    struct Highchart *chart, *highchart = STAT_MALLOC(struct Highchart, nChart);
    struct Serie* serie;
    for(i = 0; i < nChart; ++i)
      highchart__init(highchart + i);

    float v, *ave = STAT_MALLOC(float, nTable);

    // for every bot
    for(i = 0; i < nTable; ++i)
    {
      chart = highchart + i + 1;
      highchart__set_render_target(chart, tablenames[i]);
      highchart__set_title(chart, tablenames[i]);

      // xAxis
      highchart__init_axis(chart, AXIS_X, 1);
      highchart__set_axis_title(chart, AXIS_X, 0, "date");
      highchart__set_axis_category(chart, AXIS_X, 0, CATEGORY_STR, nData[i]);

      for(j = 0; j < nData[i]; ++j)
      {
        sprintf(buffer, "%d-%d-%d", datas[i][j].day, datas[i][j].month, datas[i][j].year);
        chart->xAxis[0].category_str[j] = str__dup(buffer);
      }

      // yAxis
      highchart__init_axis(chart, AXIS_Y, 2);
      highchart__set_axis_title(chart, AXIS_Y, 0, "percentage");
      highchart__set_axis_title(chart, AXIS_Y, 1, "number of doors");

      // plotoptions
      highchart__set_plotoption(chart, PLOTOPTIONS_DATALABELS, 1);
      highchart__set_plotoption(chart, PLOTOPTIONS_MOUSETRACKING, 0);

      // series
      highchart__set_series(chart, 3);
      
      serie = chart->series;
      k = 0;
      
      // percentage
      ave[i] = 0;
      highchart__set_serie_name(chart, k, "PERCENTAGE");
      highchart__set_serie(chart, SERIE_TYPE_COLUMN, 0, k, SERIE_DATATYPE_FLOAT, nData[i]);
      for(j = 0; j < nData[i]; ++j)
      {
        serie->data_float[j] = v = datas[i][j].doordisc / (float)datas[i][j].doorlvl;
        ave[i] += v;
      }
      ave[i] /= nData[i];

      // doorlvl
      ++serie; ++k;
      highchart__set_serie_name(chart, k, "DOORLVL");
      highchart__set_serie(chart, SERIE_TYPE_LINE, 1, k, SERIE_DATATYPE_INT, nData[i]);
      for(j = 0; j < nData[i]; ++j)
        serie->data_int[j] = datas[i][j].doorlvl;

      // doordisc
      ++serie; ++k;
      highchart__set_serie_name(chart, k, "DOORDISC");
      highchart__set_serie(chart, SERIE_TYPE_LINE, 1, k, SERIE_DATATYPE_INT, nData[i]);
      for(j = 0; j < nData[i]; ++j)
        serie->data_int[j] = datas[i][j].doordisc;
    }

    // general data
    chart = highchart;
    chart->chart.type = CHART_TYPE_BAR;
    highchart__set_render_target(chart, "avepercent");
    highchart__set_title(chart, "Average Percentage");

    highchart__init_axis(chart, AXIS_X, 1);
    highchart__set_axis_title(chart, AXIS_X, 0, "Bots");
    highchart__set_axis_category(chart, AXIS_X, 0, CATEGORY_STR, nTable);
    for(i = 0; i < nTable; ++i)
      chart->xAxis[0].category_str[i] = str__dup(tablenames[i]);

    highchart__init_axis(chart, AXIS_Y, 1);
    highchart__set_axis_title(chart, AXIS_Y, 0, "percentage");

    highchart__set_plotoption(chart, PLOTOPTIONS_DATALABELS, 1);
    highchart__set_plotoption(chart, PLOTOPTIONS_MOUSETRACKING, 0);

    highchart__set_series(chart, 1);
    serie = chart->series;
    highchart__set_serie_name(chart, 0, "percentage");
    highchart__set_serie(chart, SERIE_TYPE_NON, -1, 0, SERIE_DATATYPE_FLOAT, nTable);
    for(i = 0; i < nTable; ++i)
      serie->data_float[i] = ave[i];

    SAFE_FREE(ave);

    // generate html
    FILE* fp = fopen(argv[2], "w");
    if(fp == NULL)
    {
      fprintf(stderr, "No output: Unable to open %s\n", argv[2]);
    }
    else
    {
      fprint_html(fp, "statistiques", nChart, highchart);
    }

    fclose(fp);

    // clean highchart
    for(i = 0; i < nChart; ++i)
      highchart__uninit(highchart + i);
    SAFE_FREE(highchart);

    // clean
    for(i = 0; i < nTable; ++i)
    {
      SAFE_FREE(tablenames[i]);
      SAFE_FREE(datas[i]);
    }
    SAFE_FREE(tablenames);
    SAFE_FREE(nData);
    SAFE_FREE(datas);
  }
  else
  {
    fprintf(stderr, "No data in the database\n");
  }

  sqlite3_close(db);
	return EXIT_SUCCESS;
}
