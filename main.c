
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <math.h>

#define N 10000 // N - это количество отрезков на которое мы рубим функцию

double vyraz (double x); // прототип

static double a,b;

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    a = atof(argv[0]);
    b = atof(argv[1]);
    printf("\n");
    return 0;
}

int main(int argc, const char * argv[]) { // главная функция объявленными консольными переменными ну мало ли
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("test.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }

    double S = 0, x, h; // сами переменные

    char *sql = (char *) "SELECT * FROM main LIMIT 1;";


    const char* data = "Callback function called";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }






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
    return exp(x)*sin(x)/(x+1);;
}
