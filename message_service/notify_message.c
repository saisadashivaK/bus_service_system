#ifndef NOTIFY_MESSAGE_SEEN
#define NOTIFY_MESSAGE_SEEN

#include<mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "./../utils.c"

#define STUDENT 1
#define FACULTY 2
#define query_length 500



int notify_message(
    long int user_id, 
    int type_of_user
);

int notify_message(
    long int user_id, 
    int type_of_user
){
    // printf("What is happening ?\n");
    MYSQL * con = mysql_init(NULL); // 1
    if(con == NULL){ // 2
        fprintf(stderr, "%s\n", mysql_error(con)); // 3
        return -1; // 3
    }
    // printf("What is happening ?\n");
    if(mysql_real_connect(con, "localhost", "admin", "Admin@11235", // 4, 5 
        "bus_service_system", 0, NULL, 0) == NULL){
            finish_with_error(con); // 5
            return -1; // 5
    }
    // printf("What is happening ?\n");
    // the query string
    MYSQL_RES * res;// 6

    char query_select[query_length]; // 6
    if(type_of_user == STUDENT){ // 7
        sprintf(query_select, "SELECT * FROM `MessageStudent` WHERE `student_id`=%ld", user_id); // 8
        // printf("%s", query_select); // 8
    }else{
        sprintf(query_select, "SELECT * FROM `MessageFaculty` WHERE `faculty_id`=%ld", user_id); // 9
        
    }
    if(mysql_query(con, query_select)){ // 9
        // finish_with_error(con); // 10
        // if(mysql_errno == )
        mysql_close(con);
        return 0;
    }
    // printf("What is happening ?\n");
    res = mysql_store_result(con); // 11
    MYSQL_ROW row; // 11
    printf("Timestamp | Message\n"); //  11
    while((row = mysql_fetch_row(res))){ // 12
        printf("%s | %s\n", row[1], row[2]); // 13
    }
    mysql_free_result(res); // 14
    mysql_close(con); // 14
    return 1; // 14

}

#endif