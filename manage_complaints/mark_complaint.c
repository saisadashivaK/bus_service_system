#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>
#include "./../utils.c"
#include "./../message_service/send_message.c"



int mark_complaint(
    char * id, 
    char * type, 
    char * timestamp
){
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

    char query_select[200];
    if(atoi(type) == 1){
        sprintf(query_select, "SELECT `student_id` FROM `ComplaintStudent` WHERE `student_id`=%s AND `timestamp`=FROM_UNIXTIME(%s)", id, timestamp);
    }else{
        sprintf(query_select, "SELECT `faculty_id` FROM `ComplaintFaculty` WHERE `faculty_id`=%s AND `timestamp`=FROM_UNIXTIME(%s)", id, timestamp);
    }

    if(mysql_query(con, query_select)){
        printf("Internal error");
        finish_with_error(con);
        return -1;
    }
    MYSQL_RES * res = mysql_store_result(con);
    printf("segfault\n");
    if(mysql_num_rows(res) == 0){
        printf("No such complaint present\n");
        // mysql_free_result(res);
        mysql_close(con);
        return -1;
    }
    printf("segfault\n");
    if(create_message(atol(id), atoi(type), "Your complaint has been seen and will be acted upon\n") == -1){
        printf("There was an error in sending the message\n");
        mysql_free_result(res);
        mysql_close(con);
        return -1;
    }
    mysql_free_result(res);
    mysql_close(con);
    return 1;
}
