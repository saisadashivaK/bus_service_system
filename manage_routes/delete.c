#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include<glib.h>
#include "./../utils.c"

#define len 200


int delete_route(
    int route_num
);

int delete_route(
    int route_num
){
    MYSQL *con = mysql_init(NULL);
    if(con == NULL){
        fprintf(stderr, "%s\n", mysql_error(con));
        return 0;
    }
    if (mysql_real_connect(con, "localhost", "admin", "Admin@11235",
            "bus_service_system", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return 0;
    }
    char query_select[100];
    sprintf(query_select, "SELECT `route_num` FROM `Route` WHERE `route_num`=%d", route_num);
    if(mysql_query(con, query_select)){
        finish_with_error(con);
        return -1;
    }
    MYSQL_RES *res = mysql_store_result(con);
    if(mysql_num_rows(res) == 0){
        printf("Route does not exist to be deleted\n");
        mysql_free_result(res);
        mysql_close(con);
        return -1;
    }
    char query_delete[len];
    sprintf(query_delete, "DELETE FROM `Route` WHERE `route_num`=%d", route_num);
    if(mysql_query(con, query_delete)){
        finish_with_error(con);
        return -1;
    }
}
