#ifndef P1_EXTENSION_USER_OPERATIONS_H
#define P1_EXTENSION_USER_OPERATIONS_H

bool login_operation(FILE *file, char *file_name, t_login_user login_user, t_user_profile *profile_match);

bool registration_operation(FILE *file, char *file_name, t_user_profile profile);

#endif //P1_EXTENSION_USER_OPERATIONS_H