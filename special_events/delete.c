#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#define query_length 200


int delete_special_event(
    char * event_code
);

int delete_special_event(
    char * event_code
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
    // char confirm;
    // printf("Are you sure you want to delete the special event?? Y/N: ");
    // scanf("%c", &confirm);
    // int approved = confirm == 'Y' ? 1: 0;
    // if(!approved){
    //     printf("Special event not deleted\n");
    //     return 0;
    // }
    char query_select[query_length];
    sprintf(query_select, "SELECT * FROM `SpecialEvent` WHERE `event_code`='%s'", 
        event_code
    );
    
    if(mysql_query(con, query_select)){
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return 0;
    }
    MYSQL_RES * res = mysql_store_result(con);

    if(!mysql_fetch_row(res)){
        printf("SPECIAL EVENT DOES NOT EXIST TO BE DELETED\n");
        mysql_free_result(res);
        mysql_close(con);
        return 0;
    }
    char query_delete[query_length];

    sprintf(query_delete, "DELETE FROM `SpecialEvent` WHERE `event_code`='%s'", event_code);

    if(mysql_query(con, query_delete)){
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return 0;
    }
    printf("Successful\n");
    mysql_close(con);
    return 1;

}