#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "utilities.h"
#include "user_operations.h"

void login_operation(FILE * file, char * file_name, t_login_user login_user)
{
    t_user_profile * database = load_database(file, file_name);

    int id = 0;
    if (!validate_credentials_in_database(file, file_name, login_user.temp_username, login_user.temp_username, database, &id, true)){
        printf("Login failed, please check your credentials and try again\n");
    }

    time(&login_user.login_time);

    //initialise main menu
}

void registration_operation(FILE * file, char * file_name, t_user_profile profile)
{
    t_user_profile * database = load_database(file, file_name);


    upload_profile(file, file_name, profile, database);
}