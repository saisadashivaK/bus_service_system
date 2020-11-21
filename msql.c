#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>


void sql(){
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "Saibaba@9",
            "test", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }else{
        printf("Success\n");
    }
    mysql_query(con, "SELECT * FROM SessionInfo");
    MYSQL_RES *result = mysql_store_result(con);
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }
    mysql_close(con);
}