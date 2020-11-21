#ifndef UPDATE_INPUT_ROUTES_SEEN
#define UPDATE_INPUT_ROUTES_SEEN
#include<stdio.h>
#include<mysql.h>
#include<stdlib.h>
#include<string.h>
#include "update.c"




int update_add_input(int availability, int route_num){
    char num_stops[100];
    char stop_id[100][100], stop_name[100][100], timings[100][100], days[100][100];
    int av;
    int final_stop_id[100];

    printf("Enter the number of stops: \n");
    scanf("%s", num_stops);
    if(strlen(num_stops) > 3 || atoi(num_stops) < 2 || atoi(num_stops) > 30){
        printf("Sorry...Number of stops can range from 2 to 30 only\n");
        return -1;
    }

    for(int i = 0; i < atoi(num_stops); i++){
        printf("Enter stop id. If stop does not exist - enter -1\n");
        scanf("%s", stop_id[i]);
        if(atoi(stop_id[i]) == 0 || (atoi(stop_id[i]) < -1)){
            printf("Invalid stop id\n");
            return -1;
        }
        final_stop_id[i] = atoi(stop_id[i]);
        printf("Enter stop name - \n");
        scanf("%s", stop_name[i]);
        if(strlen(stop_name[i]) > 50){
            printf("Too long\n");
            return -1;
        }
        printf("Enter timings of the bus stop in comma separated format of HH:MM\n");
        scanf("%s", timings[i]);
        if(strlen(timings[i]) > 200){
            printf("Too long!!\n");
            return -1;
        }
        if(!valid_timings(timings[i])){
            printf("Invalid timing format\n");
            return -1;
        }
        printf("Enter days of the bus stop in comma separated format of Day of week with first letter capital or Everyday\n");
        scanf("%s", days[i]);
        if(strlen(days[i]) > 200){
            printf("Too long!!\n");
            return -1;
        }
        if(!valid_days(days[i])){
            printf("Invalid days format\n");
            return -1;
        }
    }
    return update_stops(route_num, availability, final_stop_id, stop_name, timings, days, atoi(num_stops));

}

int getAvailability(int route_num){
    MYSQL *con = mysql_init(NULL);//12
    if(con == NULL){ // 13
        fprintf(stderr, "%s\n", mysql_error(con)); // 14
        return 0; // 14
    }
    if (mysql_real_connect(con, "localhost", "admin", "Admin@11235",
            "bus_service_system", 0, NULL, 0) == NULL) //15
    {
        fprintf(stderr, "%s\n", mysql_error(con)); //16
        mysql_close(con); // 16
        return 0; // 16
    }
    char query_select[100];
    sprintf(query_select, "SELECT `availability` FROM `Route` WHERE `route_num`=%d", route_num);
    if(mysql_query(con, query_select)){
        printf("Internal error\n");
        return -1;
    }
    MYSQL_RES * res = mysql_store_result(con);
    MYSQL_ROW row = mysql_fetch_row(res);
    if(row){
        int ans = atoi(row[0]);
        mysql_free_result(res);
        mysql_close(con);
        return atoi(row[0]);
    }else{
        mysql_free_result(res);
        mysql_close(con);
        return -1;
    }

}
void update_input(){
    char route_id[100], choice[100];
    printf("Enter route id to be updated\n");
    scanf("%s", route_id);
    if(atoi(route_id) < 1){
        printf("Invalid route number\n");
        return;
    }
    printf("Do you want to change availability?y/n\n");
    scanf("%s", choice);
    if(strcmp(choice, "y") == 0){
        printf(
            "What should current availability be ?\n"
            "1. Available\n"
            "2. Not available\n"
        );
        char availability[100];
        scanf("%s", availability);
        if(strlen(availability) > 2 || atoi(availability) < 1 || atoi(availability) > 2){
            printf("Invalid option\n");
            return;
        }
        if(update_availability(atoi(route_id), atoi(availability)) == -1){
            return;
        }
    }else if(strcmp(choice, "n") == 0){
        return;
    }else{
        printf("Invalid choice \n");
        return;
    }
    printf("Do you want to change bus stops in the route ?y/n\n");
    char opt[100];
    scanf("%s", opt);
    if(strcmp(opt, "y") == 0){
        if(update_add_input(getAvailability(atoi(route_id)), atoi(route_id)) == -1){
            printf("Internal error please try again later\n");
        }
        return;
    }else if(strcmp(opt, "n") == 0){
        return;
    }else{
        printf("Invalid choice \n");
        return;
    }

}
#endif
