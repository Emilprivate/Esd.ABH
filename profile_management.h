#ifndef P1_PROTOTYPE_SETTINGS_H
#define P1_PROTOTYPE_SETTINGS_H

#endif //P1_PROTOTYPE_SETTINGS_H

#include <stdbool.h>
#include <utime.h>

#define MAX 32

typedef enum transport_options{Walk, Bicycle, Car, Bus}e_transport;

typedef struct user_profile_struct{
    int         id;
    char        name[MAX];
    char        address[MAX];
    char        username[MAX];
    char        password[MAX];
    double      longitude;
    double      latitude;
    double      max_distance;
    int         age;
    e_transport transport;
}t_user_profile;

typedef struct login_user_struct{
    bool init;
    char temp_username[MAX];
    char temp_password[MAX];
}t_login_user;

typedef struct session_struct{
    time_t login_time;
    time_t logout_time;
    time_t session_time;
}t_session;

typedef struct init_file_struct{
    FILE * file;
    char * file_name;
}t_init_file;

bool validate_credentials_in_database(FILE * file, char * file_name, char username[], char password[],
                                      t_user_profile database[], int * id, bool IDFLAG);
void upload_profile(FILE * file, char * file_name, t_user_profile profile, t_user_profile database[]);
t_user_profile * load_database(FILE * file, char * file_name);
t_user_profile terminal_create_user(int id);
t_user_profile load_profile(FILE * file, char * file_name, int id);