#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include "add_input.c"
#include "update_input.c"
#include "delete_input.c"
#include "./../utils.c"
#define MAX_SIZE 100

// Equivalence classes 
// input
// route availability: input condition: range 0 - 1
// number of bus stops: input condition: range 2 - 30
// list of stop id: input condition: { -1 (stop does not exist in db currently), the bus stop already exists, existing stop typed incorrectly }
// list of stop names: input condition: for stop_id[i] == -1 the new stop name cannot be the same as an existing stop name
// list of stop names: input condition: for stop_id[i] != -1 the new stop name must already be existing
// list of timings: the timings must be in valid format separated by commas in the format 24hr HH:MM,HH:MM,HH:MM
// days must be in proper format separated by commas with first letter Capital:{{Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday}, {Everyday}} 

void print(char arr[][100], int n){
    for(int i = 0; i < n; i++){
        printf("%s\n", arr[i]);
    }

}
void manage_routes(){
    while(1){
        char choice[100];
        printf(
            "Manage routes - \n"
            "1. Add route\n"
            "2. Update route\n"
            "3. Delete route\n"
            "4. Exit\n"
        );
        scanf("%s", choice);
        if(strlen(choice) > 2 || atoi(choice) > 4 || atoi(choice) < 1){
            printf("Invalid option chosen\n");
            continue;
        }
        switch(atoi(choice)){
            case 1:
                add_input();
                break;
            case 2:
                update_input();
                break;
            case 3:
                delete_input();
                break;
            case 4:
                return;
        }
    }

}