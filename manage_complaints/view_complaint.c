#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>

int view_complaint(
  char * admin_id
)
{
    MYSQL *con = mysql_init(NULL);
    if(con == NULL)
    {
      fprintf(stderr,"%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    
    if(mysql_real_connect(con,"localhost","admin","Admin@11235","bus_service_system",0, NULL, 0) ==NULL)
    {
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    MYSQL_RES * result;


    char query_select_student[300];
    sprintf(query_select_student, "SELECT *, UNIX_TIMESTAMP(`timestamp`) FROM `ComplaintStudent` WHERE `student_id` IN (SELECT `student_id` FROM `Student` WHERE `department`=(SELECT `department` FROM `CollegeAdmin` WHERE `administrator_id`=%s))", admin_id);
    char query_select_faculty[300];
    sprintf(query_select_faculty, "SELECT *, UNIX_TIMESTAMP(`timestamp`) FROM `ComplaintFaculty` WHERE `faculty_id` IN (SELECT `faculty_id` FROM `Faculty` WHERE `department`=(SELECT `department` FROM `CollegeAdmin` WHERE `administrator_id`=%s))", admin_id);

    if(mysql_query(con, query_select_student))
    {
      printf("Internal Error...Please try again later\n");
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    else {
    	result = mysql_store_result(con);
    	MYSQL_ROW row;
    	MYSQL_FIELD * field ;	
        printf("Student complaints\n");
    	while(field = mysql_fetch_field(result))
    	{
    		printf("%s | ", field->name);
    	}
    	printf("\n");
    	int field_num = mysql_num_fields(result);
    	while(row = mysql_fetch_row(result))
    	{
	    	for(int i = 0; i < field_num; i++)
	    	{
	    		printf("%s | ", row[i]? row[i] : "NULL");
	    	}
	    	printf("\n");
		}
		mysql_free_result(result);
        

    }
    if(mysql_query(con, query_select_faculty))
    {
      printf("Internal Error...Please try again later\n");
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    else {
    	result = mysql_store_result(con);
    	MYSQL_ROW row;
    	MYSQL_FIELD * field ;	
        printf("Faculty complaints\n");
    	while(field = mysql_fetch_field(result))
    	{
    		printf("%s | ", field->name);
    	}
    	printf("\n");
    	int field_num = mysql_num_fields(result);
    	while(row = mysql_fetch_row(result))
    	{
	    	for(int i = 0; i < field_num; i++)
	    	{
	    		printf("%s | ", row[i]? row[i] : "NULL");
	    	}
	    	printf("\n");
		}
		mysql_free_result(result);
        

    }

    mysql_close(con);
    return 1;
}

