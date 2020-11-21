#include<mysql.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>


int register_user(
    long int regist_id, 
    char * name, 
    char * passwd, 
    char * confm_pass, 
    char * department, 
    int type_of_user
){

    if(strcmp(passwd, confm_pass) != 0){
        printf("Passwords do not match\n");
        return -1;
    }
    char reg_id[100];
    sprintf(reg_id, "%ld", regist_id);
    
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

    char query[300], query_insert[500];
    if(type_of_user == 1){
        sprintf(query, "SELECT `student_id` FROM `Student` WHERE `student_id`=%s", reg_id);
        sprintf(query_insert, "INSERT INTO `Student` VALUES (%s, '%s', '%s', '%s')", reg_id, name, department, passwd);
    }else if(type_of_user == 2){
        sprintf(query, "SELECT `faculty_id` FROM `Faculty` WHERE `faculty_id`=%s", reg_id);
        sprintf(query_insert, "INSERT INTO `Faculty` VALUES (%s, '%s', '%s', '%s')", reg_id, name, department, passwd);
    }else if(type_of_user == 3){
        sprintf(query, "SELECT `administrator_id` FROM `CollegeAdmin` WHERE `administrator_id`=%s", reg_id);
        sprintf(query_insert, "INSERT INTO `CollegeAdmin` VALUES (%s, '%s', '%s', '%s')", reg_id, name, department, passwd);
    }
    printf("%s\n", query);
    MYSQL_RES * res;
    // mysql_free_result(res);
    
    if(mysql_query(con, query)){
        fprintf(stderr,"%d\n",mysql_errno(con));
        printf("Internal error\n");
        mysql_close(con);
        return -1;
    }
    res = mysql_store_result(con);
    if(mysql_num_rows(res)){
        printf("You cannot register twice\n");
        mysql_free_result(res);
        mysql_close(con);
        return 0;
    }
    mysql_free_result(res);
    printf("%s\n", query_insert);
    if(mysql_query(con, query_insert)){
        if(mysql_errno(con) == 1062){
            printf("One department can have only one administrator\n");
        }
        printf("Internal error - %d\n", mysql_errno(con));
        return -1;
    }
    printf("Successful registration\n");
    return 1;

}