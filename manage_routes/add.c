#ifndef ADD_ROUTES_SEEN
#define ADD_ROUTES_SEEN


#include<mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include<glib.h>
#include "./../utils.c"
#include<string.h>

#include<time.h>

#define contains(table, key) g_hash_table_contains(table, key)
#define lookup(table, key) g_hash_table_lookup(table, key)
#define insert(table, key, value) g_hash_table_insert(table, key, value)
#define add(table, key) g_hash_table_add(table, key)

#ifndef SIZE_SEEN
#define SIZE_SEEN

#define query_length 500
#define MAX_SIZE 10000

#endif
int stop_id[10000];
int route_id[10000];

// int stop_route[100000];
int n, k;

// void get_routes(){
//     // make connection
//     MYSQL *con = mysql_init(NULL); // 1
//     if(con == NULL){ // 2
//         printf("%s", mysql_error(con));// 3
//         return; // 3
//     }
//     if (mysql_real_connect(con, "localhost", "admin", "Admin@11235",
//             "bus_service_system", 0, NULL, 0) == NULL) //15
//     {
//         fprintf(stderr, "%s\n", mysql_error(con)); //16
//         mysql_close(con); // 16
//         return; // 16
//     }
    
//     // if(mysql_query(con, "SELECT `route_num` FROM `Route`")){
//     //     fprintf(stderr, "%s\n", mysql_error(con));
//     //     mysql_close(con);
//     //     exit(1);
//     // }
//     MYSQL_RES * res; // 4
//     // MYSQL *res = mysql_store_result(con);
//     MYSQL_ROW row; // 4
//     // n = 0; // global variable n
//     // while((row = mysql_fetch_row(res))){
//     //     route_id[n] = row[0];
//     //     stop_id[n] = row[1];
//     //     n++;
//     // }
//     // mysql_free_result(res);
//     if(mysql_query(con, "SELECT `route_number`, `stop_id` FROM `Route-Stop`")){// 5
//         // printf("Error in getting routes\n");
//         fprintf(stderr, "%s\n", mysql_error(con)); // 6
//         mysql_close(con); // 6
//         return; // 6
//     }
//     res = mysql_store_result(con); // 7
//     k = 0; // global variable k // 7
//     while((row = mysql_fetch_row(res))){ // 8
//         // stop
//         route_id[k] = atoi(row[0]); // 9
//         stop_id[k] = atoi(row[1]); // 9
//         k++; // 9
//     }
//     mysql_free_result(res); // 10
//     mysql_close(con); // 10
//     printf("routes fetched\n"); // 10
// }


int begin_transaction(MYSQL *mysql){
    if(mysql_autocommit(mysql, 0)){
        return 0;
    };
    return 1;
}
int end_transaction(MYSQL *mysql){
    if(mysql_autocommit(mysql, 1)){
        return 0;
    };
    return 1;
}

// int route_exists(int curr_stop_id[], int num_stops){
//     GHashTable* route_count = g_hash_table_new(g_int_hash, g_int_equal);
//     GHashTable* stops_set = g_hash_table_new(g_int_hash, g_int_equal);
//     printf("route_exists\n");
//     for(int i = 0;i < num_stops; i++){ // 35
//         add(stops_set, &curr_stop_id[i]); // 36
//     }
//     printf("route_exists\n");
//     int *newVal;
//     printf("%d", k);
//     for(int i = 0; i < k; i++){ // 37
//         // printf("route_exists\n");
//         if(contains(stops_set, &stop_id[i])){ // 38
//             if(contains(route_count, &route_id[i])){ // 39
//                  // 40       
//                 printf("break1\n");
//                 newVal = lookup(route_count, &route_id[i]); // 41
//                 *newVal = *newVal + 1; // 42
//                 insert(route_count, &route_id[i], &newVal); // 42
//                 if(*newVal== num_stops){ //43
//                     return 1; // 44
//                 }
//             }else{
//                 printf("break2\n");
//                 insert(route_count, &route_id[i], 0); // 45
//             }
//         }
//     }
//     return 0; // 46
// }



int add_route(
    int availability, 
    int stop_id[], 
    char  stop_name[][100], 
    char  timings[][100], 
    char  days[][100], 
    int num_stops
);

int add_route(
    int availability, 
    int stop_id[], 
    char  stop_name[][100], 
    char  timings[][100], 
    char  days[][100], 
    int num_stops
){
    
    
    // get_routes();
    MYSQL *con = mysql_init(NULL);//12
    if(con == NULL){ // 13
        fprintf(stderr, "%s\n", mysql_error(con)); // 14
        return 0; // 14
    }
    if (mysql_real_connect(con, "localhost", "admin", "Admin@11235",
            "bus_service_system", 0, NULL, 0) == NULL) //15
    {
        fprintf(stderr, "%s\n", mysql_error(con)); //16
        mysql_close(con); // 16
        return 0; // 16
    }
    
    int unique = 0; // 17
    for(int i = 0; i < num_stops; i++){  //18
        if(stop_id[i] != -1){ // 19
            
            MYSQL_RES * res; // 20
            char query_select[100];
            sprintf(query_select, "SELECT `stop_id`, `stop_name` FROM `BusStop` WHERE `stop_id`=%d", stop_id[i]);
            if(mysql_query(con, query_select)){  // 21
                finish_with_error(con); // 22
            }
            
            res = mysql_store_result(con); // 23
            if(!mysql_num_rows(res)){ // 24
                printf("Wrong input.. the stop that you have specified as existing does not exist\n"); // 25
                mysql_free_result(res); // 26
                return -1; // 25
            }

            MYSQL_ROW row = mysql_fetch_row(res);
            if(strcmp(row[1], stop_name[i]) != 0){ 
                printf("Wrong input.. the stop that you have specified as existing exists under a different name\n"); // 25
                mysql_free_result(res);
                return -1;
            }
            mysql_free_result(res); // 26
        }else{
            unique = 1; // 27
            MYSQL_RES * res; // 27
            char query_select[100];
            sprintf(query_select, "SELECT `stop_id` FROM `BusStop` WHERE `stop_name`='%s'", stop_name[i]);
            printf("%s\n", query_select);
            if(mysql_query(con, query_select)){ // 28
                finish_with_error(con); // 29
            }
            res = mysql_store_result(con);  // 30
            if(mysql_num_rows(res)){ // 31
                // printf("fjlkds\n");
                printf("Wrong input.. the stop that you have specified as not existing exists\n"); // 32
                mysql_free_result(res);
                return -1; // 32
            }
            mysql_free_result(res); // 33
        }
    }
    // if(!unique){ // 34
    //     if(route_exists(stop_id, num_stops)){ // 47
    //         printf("Invalid route... route with same bus stops exists\n"); // 48
    //         return 0; // 48
    //         // printf("Test\n");
    //     }
    // }
    
    begin_transaction(con); // 49
    // printf("Started transaction\n"); 
    char query_route_insert[query_length]; // 49
    sprintf(query_route_insert, "INSERT INTO `Route`(`availability`) VALUES (%d)", availability); // 49
    if(mysql_query(con, query_route_insert)){ //50
        mysql_rollback(con); // 51
        finish_with_error(con); // 51

    }
    printf("Route inserted\n");
    int route_key = mysql_insert_id(con); // 52
    // printf("got route_key: %d\n", route_key);
    for(int i = 0; i < num_stops; i++){ // 53
        // printf("%s\n", stop_name[i]);
        char query_stops_insert[query_length]; // 54
        
        sprintf(query_stops_insert, "INSERT INTO `BusStop`(`stop_name`) VALUES ('%s')", stop_name[i]); // 54
        // printf("Query is %s\n", query_stops_insert);
        if(stop_id[i] == -1){ // 55     
            if(mysql_query(con, query_stops_insert)){
                printf("bus\n");
                if(mysql_errno(con) != 1062){    
                    mysql_rollback(con);
                    
                    finish_with_error(con);
                    return -1;
                }

            }
            int stop_key = mysql_insert_id(con);
            char query_route_stops_insert[query_length];
            sprintf(query_route_stops_insert, "INSERT INTO `Route-Stop`(`route_number`, `stop_id`, `stop_seq_number`, `timing`, `days`) VALUES (%d, %d, %d, '%s', '%s')", route_key, stop_key, (i + 1), timings[i], days[i]);
            if(mysql_query(con, query_route_stops_insert)){
                printf("\nroute-stop\n%s\n", query_route_stops_insert);
                mysql_rollback(con);
                finish_with_error(con);
                return -1;
            }
        }else{
            char query_route_stops_insert[query_length];
            sprintf(query_route_stops_insert, "INSERT INTO `Route-Stop`(`route_number`, `stop_id`, `stop_seq_number`, `timing`, `days`) VALUES (%d, %d, %d, '%s', '%s')", route_key, stop_id[i], (i + 1), timings[i], days[i]);
            if(mysql_query(con, query_route_stops_insert)){
                printf("\nroute-stop\n%s\n", query_route_stops_insert);
                mysql_rollback(con);
                finish_with_error(con);
                return -1;
            }
        }
        

    }
    mysql_commit(con);
    printf("SUCCESSFUL INSERTION OF ROUTE\n");
    end_transaction(con);
    return 1;
} 

#endif