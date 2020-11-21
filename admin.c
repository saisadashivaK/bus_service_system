#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./manage_routes/manage.c"
#include "./special_events/manage.c"
#include "./manage_booking/manage.c"
#include "./manage_complaints/mark_complaint_input.c"
#include "./query.c"
void admin(
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
    char query_select[200];
    sprintf(query_select, "SELECT `department_incharge_of` FROM `CollegeAdmin` WHERE `administrator_id`=%ld", id);
    if(mysql_query(con, query_select)){
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
        "3. Manage routes\n"
        "4. Manage bookings\n"
        "5. Manage complaints\n"
        "6. Manage special events\n"
        "7. Exit\n"
        );
        scanf("%s", choice);
        if(strlen(choice) > 2 || atoi(choice) > 7 || atoi(choice) < 1){
            printf("Invalid option chosen\n");
        }
        switch(atoi(choice)){
            case 1:
                query_routes();
                break;
            case 2:
                view_special_events();
                break;
            case 3:
                manage_routes();
                break;
            case 4:
                manage_booking(reg_id);
                break;
            case 5:
                mark_complaint_input(reg_id);
                break;
            case 6:
                manage_special_event();
                break;
            case 7:
                return;
        }
    }
}