#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>
#include "msql.c"
#include "./student.c"
#include "./faculty.c"
#include "./admin.c"
// #include "special_events/add.c"
// #include "special_events/update.c"
// #include "special_events/delete.c"
// #include "message_service/notify_message.c"
// #include "message_service/send_message.c"
// #include "booking_service/booking.c"
// #include "booking_service/cancel_booking.c"
// #include "manage_routes/manage.c"
// #include "booking_service/booking.c"
// // #include "view_special_events.c"
// #include "manage_booking/view_booking.c"
// #include "manage_booking/manageBooking.c"
#include "./login/login_input.c"
#include "./login/register_input.c"
// to compile
// gcc main.c -o main `mysql_config --cflags --libs` `pkg-config --cflags --libs glib-2.0`

int main(){
    while(1){
        char option[100];
        printf("Welcome!!\n"
            "1. Login\n"
            "2. Register\n"
            "3. Exit\n"
        );
        scanf("%s", option);
        if(strlen(option) > 5 || atoi(option) < 1 || atoi(option) > 3){
            printf("Invalid option chosen\n");
        }
        int type;
        char department[200];
        long int id;
        switch(atoi(option)){
            case 1:
                
                id = login_input(&type);
                if(id > 0){
                    if(type == 1){
                        student(id);
                    }else if(type == 2){
                        faculty(id);
                    }else{
                        admin(id);
                    }
                }

                break;
            case 2:
                register_input();
                break;
            case 3:
                return 0;
        }
    }
    return 0;
}