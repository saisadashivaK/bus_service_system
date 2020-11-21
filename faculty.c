#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./view_special_events.c"
#include "./message_service/notify_message.c"
#include "./booking_service/booking_service.c"
#include "./create_complaint.c"
#include "./query.c"

void faculty(
    long int id
){
    MYSQL *con = mysql_init(NULL);
    if(con == NULL)
    {
      fprintf(stderr,"%s\n",mysql_error(con));
      printf("Internal error\n");
      mysql_close(con);
      return;
    }
    if(mysql_real_connect(con,"localhost","admin","Admin@11235","bus_service_system",0, NULL, 0) ==NULL)
    {
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return;
    }
    char query[200];
    sprintf(query, "SELECT `department` FROM `Faculty` WHERE `faculty_id`=%ld", id);
    if(mysql_query(con, query)){
        fprintf(stderr,"%s\n",mysql_error(con));
        printf("Internal error\n");
        mysql_close(con);
        return;
    }
    MYSQL_RES * res = mysql_store_result(con);
    MYSQL_ROW row = mysql_fetch_row(res);
    char department[200];
    if(row){
        sprintf(department, "%s", row[0]);
    }
    mysql_free_result(res);
    while(1){
        char reg_id[200], choice[100];
        sprintf(reg_id, "%ld", id);
        printf(
            "What would you like to do ??\n"
            "1. Query\n"
            "2. View special events\n"
            "3. Booking service\n"
            "4. View messages\n"
            "5. Complaint\n"
            "6. Exit\n"
        );
        scanf("%s", choice);
        if(strlen(choice) > 2 || atoi(choice) > 6 || atoi(choice) < 1){
            printf("Invalid option chosen\n");
            continue;
        }
        switch(atoi(choice)){
            case 1:
                query_routes();
                break;
            case 2:
                view_special_events();
                break;
            case 3:
                booking_service(reg_id, department);
                break;
            case 4:
                notify_message(atol(reg_id), 2);
                break;
            case 5:
                create_complaint(reg_id, 2);
                break;
            case 6:
                return;


        }
    }
}
