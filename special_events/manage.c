#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include "./add_input.c"
#include "./update_input.c"
#include "./delete_input.c"

void manage_special_event(){
    while(1){
        char choice[100];
        printf(
            "Manage special events- \n"
            "1. Add special event\n"
            "2. Update special event\n"
            "3. Delete special event\n"
            "4. Exit\n"
        );
        scanf("%s", choice);
        if(strlen(choice) > 2 || atoi(choice) > 4 || atoi(choice) < 1){
            printf("Invalid option chosen\n");
            continue;
        }
        switch(atoi(choice)){
            case 1:
                add_input_special_events();
                break;
            case 2:
                
                update_input_special_event();
                break;
            case 3:
                delete_special_event_input();
                // delete_input_special_events();
                break;
            case 4:
                return;
        }
    }
}