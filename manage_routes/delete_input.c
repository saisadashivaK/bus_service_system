#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./delete.c"

void delete_input(){
    char route_id[100];
    char choice[100];
    printf("Enter the route to be deleted\n");
    scanf("%s", route_id);
    printf("Are you sure ?y/n\n");
    scanf("%s", choice);
    if(strcmp(choice, "y") == 0){
        delete_route(atoi(route_id));
    }else if(strcmp(choice, "n")){
        return;
    }else{
        printf("Invalid choice\n");
        return;
    }
    
}