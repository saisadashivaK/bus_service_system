#ifndef VIEW_SPECIAL_EVENTS_SEEN
#define VIEW_SPECIAL_EVENTS_SEEN
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

int view_special_events()
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
    
    if(mysql_query(con, "SELECT * FROM SpecialEvent;"))
    {
      fprintf(stderr, "%s\n",mysql_error(con));
      mysql_close(con);
      return -1;
    }
    else {
    	result = mysql_store_result(con);
    	MYSQL_ROW row;
    	MYSQL_FIELD * field ;	
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
#endif