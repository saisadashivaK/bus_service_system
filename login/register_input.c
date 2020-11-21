#include "./register.c"

void register_input(){
        char reg_id[200], name[200], passwd[200], confm_pass[200], type[100], department[200];
        printf("Enter name: \n");
        scanf("%s", name);
        printf("Enter registration id: \n");
        scanf("%s", reg_id);
        printf("Department:\n");
        scanf("%s", department);
        printf("Enter password:\n");
        scanf("%s", passwd);
        printf("Confirm password:\n");
        scanf("%s", confm_pass);
        
        printf("Enter type of user:\n"
        "1. Student\n"
        "2. Faculty\n"
        "3. College Administrator\n"
        );
        scanf("%s", type);
        if(strlen(name) > 100){
            printf("Name cannot be at the most 100 characters\n");
            return;
        }
        if(strlen(name) < 5){
            printf("Name has be at least 5 characters\n");
            return;
        }
        if(atoi(type) == 1 || atoi(type) == 2 || atoi(type)){
            if(register_user(atol(reg_id), name, passwd, confm_pass, department, atoi(type)) == 1){
                return;
            }
        }else{
            printf("Invalid input\n");
            return;
        }

}