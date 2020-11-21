#ifndef ADD_INPUT_SPECIAL_EVENT
#define ADD_INPUT_SPECIAL_EVENT
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "./add.c"

void add_input_special_events(){
    char event_code[100], name[100], date[100], pick_up_time[100], drop_time[100], pick_up_location[100], drop_location[100], bus_driver_name[100], bus_contact_num[100];
    printf("Special event details\n");
    printf("Enter event code\n");
    scanf("%s", event_code);
    if(strlen(event_code) > 10){
        printf("Event code is too long\n");
        return;
    }
    printf("Enter name of event\n");
    scanf("%s", name);
    if(strlen(name) > 50){
        printf("Event name is too long\n");
        return;
    }

    printf("Enter date of event\n");
    scanf("%s", date);



    printf("Enter pick up time\n");
    scanf("%s", pick_up_time);
    struct tm tm = {0};
    if(strptime(pick_up_time, "%H:%M", &tm) == NULL){
        printf("Invalid time format\n");
        return;
    }

    printf("Enter drop time\n");
    scanf("%s", drop_time);
    struct tm tm1 = {0};
    if(strptime(pick_up_time, "%H:%M", &tm1) == NULL){
        printf("Invalid time format\n");
        return;
    }
    
    printf("Enter pick up location\n");
    scanf("%s", pick_up_location);
    if(strlen(pick_up_location) > 50){
        printf("Too long\n");
        return;
    }

    printf("Enter drop location\n");
    scanf("%s", drop_location);
    if(strlen(drop_location) > 50){
        printf("Too long\n");
        return;
    }

    printf("Enter bus driver name\n");
    scanf("%s", bus_driver_name);
    if(strlen(bus_driver_name) > 100){
        printf("Too long\n");
        return;
    }
    printf("Enter bus contact number\n");
    scanf("%s", bus_contact_num);
    if(atol(bus_contact_num) == 0 || strlen(bus_contact_num) != 10){
        printf("Invalid mobile number\n");
        return;
    }

    int status = add_special_event(
        event_code, 
        name, 
        date, 
        pick_up_time, 
        drop_time,
        pick_up_location, 
        drop_location,
        bus_driver_name, 
        bus_contact_num
    );

    // if(status != 1){
    //     printf("Failed\n");
    // }

}
#endif