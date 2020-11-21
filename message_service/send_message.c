#ifndef SEND_MESSAGE_SEEN
#define SEND_MESSAGE_SEEN

#include<mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "./../utils.c"
#include<string.h>


#define STUDENT 1
#define FACULTY 2
#define query_length 500




int create_message(
    long int recipient_id, 
    int type_of_user, 
    char * message
);


int create_message(
    long int recipient_id, 
    int type_of_user, 
    char * message_text
){
    if(type_of_user < 1 || type_of_user > 2){
        printf("Invalid type of user\n");
        return -1;
    }
    if(strlen(message_text) > 1000){
        printf("Message length is too long\n");
        return -1;
    }
    MYSQL * con = mysql_init(NULL);
    if(con == NULL){
        fprintf(stderr, "%s\n", mysql_error(con));
        return -1;
    }

    if (mysql_real_connect(con, "localhost", "admin", "Admin@11235",
            "bus_service_system", 0, NULL, 0) == NULL)
    {
        finish_with_error(con);
        return -1;
    }


    char query_insert[query_length];
    if(type_of_user == STUDENT){
        sprintf(query_insert, "INSERT INTO `MessageStudent` VALUES (%ld, FROM_UNIXTIME(%ld), '%s')", recipient_id, time(NULL), message_text);
        if(mysql_query(con, query_insert)){
            finish_with_error(con);
            return -1;
        }
    }else{
        sprintf(query_insert, "INSERT INTO `MessageFaculty` VALUES (%ld, FROM_UNIXTIME(%ld), '%s')", recipient_id, time(NULL), message_text);
        if(mysql_query(con, query_insert)){
            finish_with_error(con);
            return -1;
        }
    }
    printf("Message sent successfully\n");
    mysql_close(con);
    return 1;
}

#endif