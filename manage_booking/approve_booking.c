#ifndef APPROVE_BOOKING_SEEN
#define APPROVE_BOOKING_SEEN

#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "./../message_service/send_message.c"

int approve_booking(
long int faculty_id, 
int status, 
long int admin_id, 
char * department_name, 
char * driver_name, 
char * driver_number, 
char * license_plate_number
)
{
    // printf("seg\n");

    
    MYSQL *con = mysql_init(NULL);
    if(con == NULL)
    {
      fprintf(stderr,"%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    // printf("seg\n");
    
    if(mysql_real_connect(con,"localhost","admin","Admin@11235","bus_service_system",0, NULL, 0) ==NULL)
    {
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    MYSQL_RES * result;

    char query_dep_exists[200];
    sprintf(query_dep_exists, "SELECT `administrator_id` FROM `CollegeAdmin` WHERE `department_incharge_of`='%s'", department_name);
    if(mysql_query(con, query_dep_exists)){
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    // printf("seg\n");
    result = mysql_store_result(con);
    if(!mysql_num_rows(result)){
      printf("Wrong input... No such department exists\n");
      mysql_free_result(result);
      mysql_close(con);
      return -1;
    }
    mysql_free_result(result);
    
    // printf("seg\n");

    char query_select_dep[200];
    sprintf(query_select_dep, "SELECT `department_incharge_of` FROM `CollegeAdmin` WHERE `administrator_id`=%ld", admin_id);
    printf("%s\n", query_select_dep);
    if(mysql_query(con, query_select_dep)){
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    result = mysql_store_result(con);
    MYSQL_ROW row = mysql_fetch_row(result);
    
    if(row && strcmp(row[0], department_name) != 0){
      printf("You are not authorized to approve bookings of other departments\n") ;
      mysql_free_result(result);
      mysql_close(con);
      return -1;
    }
    // printf("seg\n");
    mysql_free_result(result);

    
    char query_update[200];
    printf("%s\n", query_update);
    sprintf(query_update, "UPDATE `Booking` SET `booking_status`=%d, `approved_by`=%ld WHERE `faculty_id`=%ld", status, admin_id, faculty_id);
    if(mysql_query(con, query_update))
    {
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    // printf("seg\n");
    char message_text[1010];
    if(status == 0){
        sprintf(message_text, "Your booking has been rejected\n");
        create_message(faculty_id, 2, message_text);
        return 1;
    }
    char query_select[200];
    sprintf(query_select, "SELECT * FROM `Booking` WHERE `faculty_id`=%ld", faculty_id);
    if(mysql_query(con, query_select)){
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    result = mysql_store_result(con);
    MYSQL_FIELD * field ;	
    // printf("\n");
    row = mysql_fetch_row(result);
    // printf("seg\n");
    if(row){
        sprintf(message_text, "Your request has been approved.\n Following are the details: \n faculty_id: %s\n  Department: %s\n Start location: %s\n End location: %s\nBooking_status: %s\nApproved_by: %s\ndate: %s\nstart time: %s\nend time: %s\ndriver_name: %s\ndriver_number: %s\nbus_license_plate_number: %s\n",
        row[0], 
        row[1], 
        row[2], 
        row[3],
        "Approved", 
        row[5], 
        row[6], 
        row[7], 
        row[8], 
        driver_name, 
        driver_number, 
        license_plate_number
        );
    }
    printf("%s\n", message_text);
    mysql_free_result(result);
    mysql_close(con);
    if(strlen(message_text) > 1000){
      printf("Details of bus were too long... make it shorter\n");
      return -1;
    }
    create_message(faculty_id, 2, message_text);
    printf("SUCCESS\n");
    return 1;
}

#endif