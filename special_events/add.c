#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#define query_length 400

int add_special_event(
    char * event_code, 
    char * name, 
    char * date, 
    char * pick_up_time, 
    char * drop_time, 
    char * pick_up_location, 
    char * drop_location, 
    char * bus_driver_name, 
    char * bus_contact_num
);

int add_special_event(
    char * event_code, 
    char * name, 
    char * date, 
    char * pick_up_time, 
    char * drop_time, 
    char * pick_up_location, 
    char * drop_location, 
    char * bus_driver_name, 
    char * bus_contact_num
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
        return -1;
    }
    char query_select[query_length];
    char query_insert[query_length];
    sprintf(query_select, "SELECT * FROM `SpecialEvent` WHERE `event_code`='%s'", 
        event_code
    );
   
    if(mysql_query(con, query_select)){
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return -1;
    }
    MYSQL_RES * res = mysql_store_result(con);

    if(mysql_fetch_row(res)){
        printf("THE RECORD ALREADY EXISTS\n");
        mysql_close(con);
        return -1;
    }
    sprintf(query_insert, "INSERT INTO `SpecialEvent` VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", 
        event_code, 
        name, 
        date, 
        pick_up_time, 
        drop_time, 
        pick_up_location, 
        drop_location, 
        bus_driver_name, 
        bus_contact_num
    );
    printf("%s", query_insert);
    if(mysql_query(con, query_insert)){
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return 0;
    }
    printf("Successful\n");
    mysql_close(con);
    return 1;
  
}


