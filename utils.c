#ifndef UTILS_SEEN
# define UTILS_SEEN
#include<mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


void finish_with_error(MYSQL *con){
    fprintf(stderr, "%d %s\n", mysql_errno(con), mysql_error(con));
    mysql_close(con);
    return;
}

#endif