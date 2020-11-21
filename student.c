#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./view_special_events.c"
#include "./message_service/notify_message.c"
#include "./create_complaint.c"
#include "./query.c"

void student(
    long int id
){
    while(1){
        char reg_id[200], choice[100];
        sprintf(reg_id, "%ld", id);
        printf(
            "What would you like to do ??\n"
            "1. Query\n"
            "2. View special events\n"
            "3. View messages\n"
            "4. Complaint\n"
            "5. Exit\n"
        );
        scanf("%s", choice);
        if(strlen(choice) > 2 || atoi(choice) > 5 || atoi(choice) < 1){
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
                notify_message(atol(reg_id), 1);
                break;
            case 4:
                create_complaint(reg_id, 1);
                break;
            case 5:
                return;


        }
    }
}