#include "./login.c"

long int login_input(int *type_of_user){
    while(1){
        char reg_id[100], password[100], type[100];

        printf("Enter id number:\n");
        scanf("%s", reg_id);
        printf("Enter password:\n");
        scanf("%s", password);
        printf("Enter type of user:\n"
        "1. Student\n"
        "2. Faculty\n"
        "3. College Administrator\n"
        );
        scanf("%s", type);
        if(atoi(type) == 1 || atoi(type) == 2 || atoi(type) == 3){
            if(login(reg_id, password, atoi(type)) == 1){
                *type_of_user = atoi(type);
                return atol(reg_id);
            }else{
                return 0;
            }
        }else{
            printf("Invalid input\n");
            return -1;
        }
    }
}