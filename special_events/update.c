#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#define query_length 400

int update_special_event(
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

int update_special_event(
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
        return 0;
    }
    char query_select[query_length];
    char query_update[query_length];
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
        printf("RECORD DOES NOT EXIST TO BE UPDATED\n");
        mysql_free_result(res);
        return 0;
    }
    mysql_free_result(res);
    sprintf(query_update, "UPDATE `SpecialEvent` SET `event_code`='%s', `name`='%s', `date`='%s', `pick_up_time`='%s', `drop_time`='%s', `pick_up_location`='%s', `drop_location`='%s', `bus_driver_name`='%s', `bus_contact_num`='%s'", 
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
    printf("%s\n", query_update);
    if(mysql_query(con, query_update)){
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        return 0;
    }
    printf("Successful\n");
    

    mysql_close(con);
    return 1;

} 