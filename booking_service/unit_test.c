#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./cancel_booking.c"
#include "./booking_input.c"
#include "./booking_service.c"
#include "./booking.c"

void test_booking(){
    long int faculty_id;
    char start[100], end[100], date[100], start_time[100], end_time[100], department[100];
    scanf("%ld %s %s %s %s %s %s", start, end, date, start_time, end_time, department);
    booking(
        faculty_id, 
        start, 
        end, 
        date, 
        start_time, 
        end_time, 
        department
    );
}

void test_cancel_booking(){
    long int faculty_id;
    char date[100];
    scanf("%ld %s", faculty_id, date);
}

void test_booking_service(){

}