
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <math.h>

#define N 10000 // N - это количество отрезков на которое мы рубим функцию

double vyraz (double x); // прототип
void execute(int rc, sqlite3 *db, char *sql, char *zErrMsg);
void createtable(int rc, sqlite3 *db, char *sql, char *zErrMsg);
void insert(int rc, sqlite3 *db, char *sql, char *zErrMsg);
static double a,b;

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    if(argv[0] && argv[1]){
        a = atof(argv[0]);
        b = atof(argv[1]);
    }
    printf("\n");
    return 0;
}

int main(int argc, const char * argv[]) { // главная функция объяв
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("KURWA.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }

    double S = 0, x, h; // сами переменные

    char *sql = (char *) "SELECT * FROM segment LIMIT 1;";
    char *createsql = (char *) "CREATE TABLE segment (a DECIMAL(10,5),b DECIMAL(10,5))";

    char *insertsql = (char *) "insert into segment  values (2,5)";
    execute(rc,db,sql,zErrMsg);
    createtable(rc,db,createsql,zErrMsg);
    insert(rc,db,insertsql,zErrMsg);


    //отрезок [a, b] разобьем на N частей
    h = (b - a)/N;
    x = a + h;
    while (x < b)
    {
        S = S + 4*vyraz(x);
        x = x + h;
        //проверяем не вышло ли значение x за пределы полуинтервала [a, b]
        if (x >= b) break;
        S = S + 2*vyraz(x);
        x = x + h;
    }

    S = (h/3)*(S + vyraz(a) + vyraz(b));
    printf ("%.5lf\n", S);
    return 0;
}


double vyraz(double x){
    return exp(x)*sin(x)/(x+1);
}

void execute(int rc, sqlite3 *db, char *sql, char *zErrMsg){
    const char* data = "Callback function called";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }
}
void createtable(int rc, sqlite3 *db, char *sql, char *zErrMsg){
    const char* data = "Callback function called";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }
}
void insert(int rc, sqlite3 *db, char *sql, char *zErrMsg){
    const char* data = "Callback function called";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }
}