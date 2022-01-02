#ifndef DB_
#define DB_

#define MAXSIZE 100

//err code
#define DBFULL 1	/* database is full */


typedef struct{
	struct{
		char car[1000];
	}users[MAXSIZE];
	int num;
}DB;
typedef struct{
	struct{
		char car1[6];
		}users[MAXSIZE];
	int num;
}DB1;
typedef struct{
	struct{
		char carnum[6];
		}Person[MAXSIZE];
	int num;
}PE;

int db_load(DB *database, const char *dbfile);
int db_save(DB *database, const char *dbfile);
int db_init(DB *database);
int db_insert(DB *database,  char *car);

int db_load1(PE *Persona, const char *dbfile);
int db_save1(PE *Persona, const char *dbfile);
int db_init1(PE *Persona);
//int db_insert1(PE *Personal,  char *carnum);
//int db_delete(DB *database, const char *name, const char *pass);
//int db_update(DB *database, const char *name, const char *pass, const char *passnew);
//int db_select(DB *database, const char *name, const char *pass);
void db_show(DB *database, char *buf);


#endif

