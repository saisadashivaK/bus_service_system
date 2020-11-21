#ifndef QUERY_SEEN
#define QUERY_SEEN
#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include <string.h>



void query1(int start, int end)
{
	MYSQL * con = mysql_init(NULL);
	if(con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		return;
	}
	// printf("segfault\n");
	if(mysql_real_connect(con, "localhost", "admin", "Admin@11235", "bus_service_system", 0, NULL, 0) == NULL)
	{
		finish_with_error(con);
        return;
	}
	char query[300];
	sprintf(query, "SELECT DISTINCT t1.route_number, t1.stop_seq_number AS start, t2.stop_seq_number  AS end FROM `Route-Stop` t1, `Route-Stop` t2 WHERE t1.stop_id = %d AND t2.stop_id = %d AND t1.route_number = t2.route_number", start, end); 
	if(mysql_query(con, query))
	{
		finish_with_error(con);
        return;
	}
    // printf("segfault\n");
	MYSQL_RES * result = mysql_store_result(con);

	MYSQL_RES * routes ;
	MYSQL_ROW row, tuple;
	MYSQL_FIELD * field;
	int num;
    if(mysql_num_rows(result) == 0){
        printf("No particular route found\n");
        return;
    }

	while(row = mysql_fetch_row(result))
	{
        // printf("segfault\n");
        int st, stop;
        char ord[100];
        if(atoi(row[1]) >= atoi(row[2])){
            st = atoi(row[2]);
            stop = atoi(row[1]);
            sprintf(ord, "DESC");
        }else{
            st = atoi(row[1]);
            stop = atoi(row[2]);
            sprintf(ord, "ASC");
        }
		sprintf(query, "SELECT route_number, stop_id, stop_seq_number FROM `Route-Stop` where route_number = %d AND stop_seq_number BETWEEN %d AND %d ORDER BY `route_number`, `stop_seq_number` %s", atoi(row[0]), st, stop, ord); 	
        printf("%s\n", query);
		if(mysql_query(con, query))
		{
			finish_with_error(con);
            return;	
		}
		routes = mysql_store_result(con);
		num = mysql_num_fields(routes);
		while(field = mysql_fetch_field(routes))
		{
			printf("%s\t", field->name);
		}
		printf("\n");
		while(tuple = mysql_fetch_row(routes))
		{
			for(int i = 0; i < num; i++)
			{
				printf("%s\t", tuple[i]);
			}
			printf("\n");
		}
		mysql_free_result(routes);
	}
	mysql_free_result(result);
	mysql_close(con);
	
}


void query2(int stop)
{
	MYSQL *  con = mysql_init(NULL);
	if(con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		return;
	}
	if(mysql_real_connect(con, "127.0.0.1", "admin", "Admin@11235", "bus_service_system", 0, NULL, 0) == NULL)
	{
		finish_with_error(con);
        return;
	}
    
	char query[200];
	sprintf(query, "SELECT route_num FROM Route, `Route-Stop` WHERE stop_id = %d AND route_num = route_number", stop);
	if(mysql_query(con, query))
	{
		finish_with_error(con);
        return;
	}
	MYSQL_RES * result = mysql_store_result(con);
	MYSQL_ROW row;
	MYSQL_FIELD * field;
	int num = mysql_num_fields(result);
	while(field =  mysql_fetch_field(result))
	{
		printf("%s\t", field->name);
	}
	printf("\n");
	while(row = mysql_fetch_row(result))
	{
		for(int i = 0; i < num; i++)
		{
			printf("%s\t",row[i] ? row[i] : "NULL") ;
		}
		printf("\n");
	}
    mysql_free_result(result);
	mysql_close(con);
}


void query3(int route)
{
	MYSQL * con = mysql_init(NULL);
	if(con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		return;
	}
	if(mysql_real_connect(con, "127.0.0.1", "admin", "Admin@11235", "bus_service_system", 0, NULL, 0) == NULL)
	{
		finish_with_error(con);
        return;
	}
	char * query;
	sprintf(query, "SELECT stop_id, stop_seq_number, timing, days FROM `Route-Stop` WHERE route_number = %d ;", route);   
	if(mysql_query(con, query))
	{
		finish_with_error(con);
        return;
	}
	MYSQL_RES * result = mysql_store_result(con);
	MYSQL_ROW row;
	int num = mysql_num_fields(result);
	MYSQL_FIELD * field ;
	while(field = mysql_fetch_field(result))
	{
		printf("%s\t", field->name);
	}
	printf("\n");
	while(row = mysql_fetch_row(result))
	{
		for(int i = 0; i < num; i++)
		{
			printf("%s\t", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}
	mysql_close(con);
}


int query_routes()
{
	char type[100], route[100], start[100], end[100], stop[100];
	
	printf("query 1 : Route from start and end stop \n");
	printf("query 2 : Routes include a particular stop \n");
	printf("query 3 : Information of a aprticular route \n");  
    printf("4 - Exit\n");  
	
	printf("For query 1 enter 1 \nFor query 2 enter 2 \nFor query 3 enter 3 \n For exit enter 4\n");
	scanf("%s", type);
    if(strlen(type) > 2 || atoi(type) > 4 || atoi(type) < 1){
        return -1;
    }
	
	switch(atoi(type))
	{
		case 1 : 
            printf("Start stop : ");
            scanf("%s", start);
            printf("End stop : ");
            scanf("%s", end);
            query1(atoi(start), atoi(end));
            break;
		case 2 : printf("Stop name : ");
			 scanf("%s", stop);
			 query2(atoi(stop));
			 break;
		case 3 : printf("Route number : ");
			 scanf("%s", route);
			 query3(atoi(route));
			 break;
		case 4: 
			return 1;
	}
	

	return 0;	
}
#endif