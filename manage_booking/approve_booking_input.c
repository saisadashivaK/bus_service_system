#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./approve_booking.c"

void approve_booking_input(long int admin_reg_id){ 

    char faculty_id[100], status[100], admin_id[100], department_name[100], driver_name[100], driver_number[100], license_plate_number[100];
    sprintf(admin_id, "%ld", admin_reg_id);
    printf("Enter faculty id who made the booking\n");
    scanf("%s", faculty_id);
    printf(
        "Enter status of booking\n"
        "0 - Rejected\n"
        "1 - Approved\n"
    );
    scanf("%s", status);
    if(strlen(status) > 2 || atoi(status) != 0 && atoi(status) != 1){
      printf("Status can have values in the range 0 to 1 only\n");
      return;
    }
    printf("Enter the name of the department of the faculty who made the booking:\n");
    scanf("%s", department_name);
    if(strlen(department_name) > 100){
        printf("Too long...\n");
        return;
    }
    printf("Enter the name of the driver:\n");
    scanf("%s", driver_name);
    if(strlen(driver_name) > 100){
        printf("Sorry name is too long\n");
        return;
    }
    printf("Enter number driver\n");
    scanf("%s", driver_number);
    if(strlen(driver_number) != 10){
        printf("Incorrect length of driver number\n");
    }
    printf("Enter license plate number: \n");
    scanf("%s", license_plate_number);
    if(strlen(license_plate_number) != 10){
        printf("Incorrect length of license plate number\n");
        return;
    }
    approve_booking(
        atol(faculty_id), 
        atoi(status), 
        atol(admin_id),
        department_name, 
        driver_name, 
        driver_number, 
        license_plate_number 
    );


    
}