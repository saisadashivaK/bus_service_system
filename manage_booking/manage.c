#include<stdio.h>
#include <stdlib.h>
#include "./approve_booking_input.c"
#include "./view_booking.c"


void manage_booking(char * admin_id){
    char faculty_id[100];
    char status[100];
    char department_name[200], driver_name[200], driver_number[200], license_plate_number[200];
    printf("Manage booking requests:\n");
    printf(
        "1. View bookings\n"
        "2. Approve booking\n"
        "3. Exit\n"
    );
    char choice[100];
    scanf("%s", choice);
    if(atoi(choice) < 1 || atoi(choice) > 3){
        printf("Invalid choice.");
        return;
    }
 

    if(atoi(choice) == 1){
        view_booking(atol(admin_id));
    }else if(atoi(choice) == 2){
        approve_booking_input(atol(admin_id));
    }else{
        return;
    }  
    return;


}

