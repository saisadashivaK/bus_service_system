#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "./view_complaint.c"
#include "./mark_complaint.c"


void mark_complaint_input(
    char * admin_id
){
    char choice[100], comp_id[100], type[100], timestamp[200];
    
    view_complaint(admin_id);

    printf(
        "\nDo you want to mark a complaint as seen"
        "If you mark it as seen a message will be sent to the complainant\n"
        "Select one of the options\n"
        "1. Mark\n"
        "2. Exit\n"
    );
    scanf("%s", choice);
    if(strlen(choice) > 2 || atoi(choice) > 2 || atoi(choice) < 1){
        printf("Invalid option chosen\n");
        return;
    }
    if(atoi(choice) == 1){
        printf("Enter id of complainant:\n");
        scanf("%s", comp_id);
        printf(
            "Enter type of user -\n"
            "1. Student\n"
            "2. Faculty\n"
        );
        scanf("%s", type);
        if(strlen(type) > 2 || atoi(type) > 2 || atoi(type) < 1){
            printf("Invalid option chosen\n");
            return;
        }
        printf("Enter unix timestamp of message: \n");
        scanf("%s", timestamp);
        printf("segfault\n");
        mark_complaint(comp_id, type, timestamp);

    }else{
        return;
    }


}

