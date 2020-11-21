#include<mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


int login(char *reg_id, char *passwd, int type_of_user){

    MYSQL *con = mysql_init(NULL);
    if(con == NULL)
    {
      fprintf(stderr,"%s\n",mysql_error(con));
      printf("Internal error\n");
      mysql_close(con);
      return -1;
    }
    if(mysql_real_connect(con,"localhost","admin","Admin@11235","bus_service_system",0, NULL, 0) ==NULL)
    {
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }

    char query[300];
    if(type_of_user == 1){
        sprintf(query, "SELECT * FROM `Student` WHERE `student_id`=%s AND `password`='%s'", reg_id, passwd);
    }else if(type_of_user == 2){
        sprintf(query, "SELECT * FROM `Faculty` WHERE `faculty_id`=%s AND `password`='%s'", reg_id, passwd);
    }else if(type_of_user == 3){
        sprintf(query, "SELECT * FROM `CollegeAdmin` WHERE `administrator_id`=%s AND `password`='%s'", reg_id, passwd);
    }
    
    if(mysql_query(con, query)){
        fprintf(stderr,"%s\n",mysql_error(con));
        printf("Internal error\n");
        mysql_close(con);
        return -1;
    }
    MYSQL_RES * res = mysql_store_result(con);
    if(!mysql_num_rows(res)){
        printf("Sorry.. Username or password is incorrect\n");
        mysql_free_result(res);
        mysql_close(con);
        return 0;
    }
    return 1;

}