#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include "./delete.c"

void delete_special_event_input(){
    char event_code[100];
    char choice[100];
    printf("Enter event code of the special event to be deleted\n");
    scanf("%s", event_code);
    if(strlen(event_code) > 10){
        printf("Too long..\n");
        return;
    }
    printf("Are you sure ?y/n\n");
    scanf("%s", choice);
    if(strcmp(choice, "y") == 0){
        delete_special_event(event_code);
    }else if(strcmp(choice, "n")){
        return;
    }else{
        printf("Invalid choice\n");
        return;
    }

}