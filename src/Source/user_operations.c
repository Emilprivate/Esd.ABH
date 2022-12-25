#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "../Definitions/struct_definitions.h"

#include "../Header/user_operations.h"
#include "../Header/profile_management.h"
#include "../Header/utilities.h"

bool login_operation(FILE * file, char * file_name, t_login_user login_user, t_user_profile * profile_match)
{
    t_user_profile * database = load_database(file, file_name);

    int id = 0;

    if (!validate_credentials_in_database(file, file_name, login_user.temp_username, login_user.temp_password,database, &id, true))
    {
        return false;
    }

    *profile_match = database[id];

    return true;
}

bool registration_operation(FILE * file, char * file_name, t_user_profile profile)
{
    profile.id = count_lines_in_file(file, file_name);

    t_user_profile * database = load_database(file, file_name);
    upload_profile(file, file_name, profile, database);

    return true;
}