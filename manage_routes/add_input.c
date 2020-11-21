
#ifndef ADD_INPUT_ROUTES_SEEN
#define ADD_INPUT_ROUTES_SEEN

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./add.c"


int valid_timings(char * datestring){
    char * time = strtok(datestring, ",");
    while(time != NULL){
        struct tm tm = {0};
        if(strptime(time, "%H:%M", &tm) == NULL){
            printf("Invalid time format\n");
            return 0;
        }
        time = strtok(NULL, ",");
    }
    return 1;
}

int presentDay(char * day){
    char days[][20] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Everyday"};
    for(int i = 0; i < 8; i++){
        // printf("%s %s\n", day, day[i]);
        if(strcmp(day, days[i]) == 0){
            
            return 1;
        }
    }
    return 0;
}

int valid_days(char * daystring){
    char * day = strtok(daystring, ",");
    while(day != NULL){
        if(!presentDay(day)){
            printf("Format of days is wrong\n");
            return 0;
        }
        day = strtok(NULL, ",");
    }
    return 1;
}

void add_input(){
    char num_stops[100];
    char availability[100], stop_id[100][100], stop_name[100][100], timings[100][100], days[100][100];
    int av;
    int final_stop_id[100];

    printf("Enter the number of stops: \n");
    scanf("%s", num_stops);
    if(strlen(num_stops) > 3 || atoi(num_stops) < 2 || atoi(num_stops) > 30){
        printf("Sorry...Number of stops can range from 2 to 30 only\n");
        return;
    }
    printf("Is the route going to be available from now ? y/n\n");
    scanf("%s", availability);
    if(strcmp(availability, "y") == 0){
        av = 1;
    }else if(strcmp(availability, "n") == 0){
        av = 0;
    }else{
        printf("Invalid availability status\n");
        return;
    }

    for(int i = 0; i < atoi(num_stops); i++){
        printf("Enter stop id. If stop does not exist - enter -1\n");
        scanf("%s", stop_id[i]);
        if(atoi(stop_id[i]) == 0 || (atoi(stop_id[i]) < -1)){
            printf("Invalid stop id\n");
            return;
        }
        final_stop_id[i] = atoi(stop_id[i]);
        printf("Enter stop name - \n");
        scanf("%s", stop_name[i]);
        if(strlen(stop_name[i]) > 50){
            printf("Too long\n");
            return;
        }
        printf("Enter timings of the bus stop in comma separated format of HH:MM\n");
        scanf("%s", timings[i]);
        if(strlen(timings[i]) > 200){
            printf("Too long!!\n");
            return;
        }
        if(!valid_timings(timings[i])){
            printf("Invalid timing format\n");
            return;
        }
        printf("Enter days of the bus stop in comma separated format of Day of week with first letter capital or Everyday\n");
        scanf("%s", days[i]);
        if(strlen(days[i]) > 200){
            printf("Too long!!\n");
            return;
        }
        if(!valid_days(days[i])){
            printf("Invalid days format\n");
            return;
        }
    }
    add_route(av, final_stop_id, stop_name, timings, days, atoi(num_stops));


}
#endif