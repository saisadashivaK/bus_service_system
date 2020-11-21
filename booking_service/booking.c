#ifndef BOOKING_SEEN
#define BOOKING_SEEN
#include<mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "./../utils.c"

#define query_length 500

int make_booking(
    long int faculty_id, 
    char * start, 
    char * end, 
    char * date, 
    char * start_time, 
    char * end_time, 
    char * department
);
int make_booking(
    long int faculty_id, 
    char * start, 
    char * end, 
    char * date, 
    char * start_time, 
    char * end_time, 
    char * department
){
    MYSQL * con = mysql_init(NULL);
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

    // char query_select[query_length];
    char query_insert[500];
    sprintf(query_insert, "INSERT INTO `Booking`(`faculty_id`, `department`, `start`, `end`, `date`, `start_time`, `end_time`) VALUES (%ld, '%s', '%s', '%s', '%s', '%s', '%s')", faculty_id, department, start, end, date, start_time, end_time);
    printf("%s\n", query_insert);
    if(mysql_query(con, query_insert)){
        if(mysql_errno(con) == 1062){
            printf("Booking for you on this date already exists\n Hence you cannot make anymore bookings on the same day\n");
        }
        finish_with_error(con);
        return -1;
    }
    printf("You have made booking successfully!!\n");
    mysql_close(con);
    return 1;
}


#endif