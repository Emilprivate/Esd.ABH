#ifndef P1_PROTOTYPE_SETTINGS_H
#define P1_PROTOTYPE_SETTINGS_H

bool validate_credentials_in_database(FILE * file, char * file_name, char username[], char password[],
                                      t_user_profile database[], int * id, bool IDFLAG);
void upload_profile(FILE * file, char * file_name, t_user_profile profile, t_user_profile database[]);
t_user_profile * load_database(FILE * file, char * file_name);
t_user_profile terminal_create_user(int id);
t_user_profile load_profile(FILE * file, char * file_name, int id);

#endif //P1_PROTOTYPE_SETTINGS_H