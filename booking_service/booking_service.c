#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "./booking_input.c"
#include "./cancel_booking.c"
#include<time.h>

void booking_service(char * faculty_id, char * department){
    char choice[100];
    printf(
        "Booking service: \n"
        "1. Create booking\n"
        "2. Cancel booking\n"
        "3. Exit\n"
        "Select an option\n"
    );
    scanf("%s", choice);
    if(strlen(choice) > 2 || atoi(choice) > 3 || atoi(choice) < 1){
        printf("Too long...\n");
        return;
    }
    if(atoi(choice) == 1){
        booking_input(faculty_id, department);
    }else if(atoi(choice) == 2){
        char date[200];
        printf("Enter date at which booking has to be cancelled(YYYY-MM-DD)\n");
        scanf("%s", date);
        struct tm tm = {0};
        if(strptime(date, "%Y-%m-%d", &tm) == NULL){
            printf("Invalid date");
            return;
        }
        cancel_booking(atol(faculty_id), date);
    }else{
        return;
    }
    
}