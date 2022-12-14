#ifndef P1_PROTOTYPE_SETTINGS_H
#define P1_PROTOTYPE_SETTINGS_H

#endif //P1_PROTOTYPE_SETTINGS_H

#include <stdbool.h>

typedef enum transport_options{Walk, Bicycle, Car, Bus}e_transport;

typedef struct user_profile_struct{
    int         id;
    char        name[30];
    char        address[30];
    char        username[30];
    char        password[30];
    double      longitude;
    double      latitude;
    double      max_distance;
    int         age;
    e_transport transport;
}t_user_profile;

bool validate_credentials_in_database(FILE * file, char * file_name, char username[], char password[],
                                      t_user_profile database[], int * id, bool IDFLAG);
void upload_profile(FILE * file, char * file_name, t_user_profile profile, t_user_profile database[]);
t_user_profile * load_database(FILE * file, char * file_name);
t_user_profile create_profile(int id);
t_user_profile load_profile(FILE * file, char * file_name, int id);