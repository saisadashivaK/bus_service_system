#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "./booking.c"

void booking_input(char * faculty_id, char * department){
    char start[200], end[200], date[200], start_time[200], end_time[200];
    printf("Enter the following booking details\n");
    printf("Start destination: \n");
    scanf("%s", start);
    if(strlen(start) > 100){
        printf("Too long...\n");
        return;
    }
    printf("End destination: \n");
    scanf("%s", end);
    if(strlen(end) > 100){
        printf("Too long...\n");
        return;
    }
    printf("Date of travel(YYYY-MM-DD):\n");
    scanf("%s", date);
    struct tm tm_date = {0};
    if(strptime(date, "%Y-%m-%d", &tm_date) == NULL){
        printf("Invalid date");
        return;
    }
    printf("Start time of journey(HH:MM 24-hr format):\n");
    scanf("%s", start_time);
    struct tm tm = {0};
    if(strptime(start_time, "%H:%M", &tm) == NULL){
        printf("Invalid time format\n");
        return;
    }
    printf("End time of journey:\n");
    scanf("%s", end_time);
    struct tm tm2 = {0};
    if(strptime(end_time, "%H:%M", &tm2) == NULL){
        printf("Invalid time format\n");
        return;
    }
    make_booking(atol(faculty_id), start, end, date, start_time, end_time, department);

}
