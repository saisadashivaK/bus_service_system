#ifndef CANCEL_BOOKING_SEEN
#define CANCEL_BOOKING_SEEN
#include<mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "./../utils.c"

#define query_length 500

int cancel_booking(
    long int faculty_id, 
    char * date
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
    char query_delete[query_length];
    sprintf(query_delete, "DELETE FROM `Booking` WHERE `faculty_id`=%ld AND `date`='%s'", faculty_id, date);
    if(mysql_query(con, query_delete)){
        finish_with_error(con);
        return -1;
    }
    mysql_close(con);
    printf("SUCCESS\n");
}

#endif