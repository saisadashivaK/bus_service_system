#ifndef CREATE_COMPLAINT_SEEN
#define CREATE_COMPLAINT_SEEN
#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void clean_stdin(void)
{
	// from stackoverflow
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
void create_complaint(char * id, int type)
{
	MYSQL * con = mysql_init(NULL);
	time_t sec;
	char query[500];
	char feed[201];
	if(con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(0);
	}
	
	if(mysql_real_connect(con, "localhost", "admin","Admin@11235","bus_service_system", 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(0);
	}
	printf("Enter your complaint or feedback in at most 200 characters \n");
	clean_stdin();
	fgets(feed, 200, stdin);

	if(type == 1)
	{	sec = time(NULL);
		sprintf(query, "INSERT INTO ComplaintStudent VALUES(%s, FROM_UNIXTIME(%ld), '%s');", id, sec, feed);
		if(mysql_query(con, query))
		{
			fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
			printf("Unsuccessful\n");
			return;
		}else{
			printf("Successful registration of complaint\n");
		}
		
	}else{
		sec = time(NULL);
		sprintf(query, "INSERT INTO ComplaintFaculty VALUES(%s, FROM_UNIXTIME(%ld), '%s');", id, sec, feed);
		if(mysql_query(con, query))
		{
			fprintf(stderr, "%s\n", mysql_error(con));
			mysql_close(con);
			printf("Unsuccessful\n");
			return;
		}else{
			printf("Successful registration of complaint\n");
		}
	
	}
	
	mysql_close(con);
	return;
}
#endif