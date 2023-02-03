#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../Definitions/struct_definitions.h"
#include "../Utilities/utilities.h"
#include "db_management.h"

#define TRANSPORT_OPTIONS 4 //Amount of transport options

bool validate_credentials_in_database(FILE *file, char *file_name, char username[], char password[],
                                      t_user_profile database[], int *id, bool IDFLAG) {

    for (int i = 0; i < count_lines_in_file(file, file_name); i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            if (IDFLAG)
                *id = i;

            return true;
        }
    }

    return false;
}

t_user_profile terminal_create_user(int id) {
    t_user_profile new_profile;

    new_profile.id = id;

    printf("\nPlease enter your product_name> ");
    scanf("%s", new_profile.name);

    printf("Please enter your age> ");
    scanf("%d", &new_profile.age);

    printf("Please enter your address> ");
    scanf("%s", new_profile.address);

    printf("Enter coordinates of your address (x.x, y.y)> ");
    scanf("%lf, %lf", &new_profile.longitude, &new_profile.latitude);

    printf("Max distance you're willing to travel> ");
    scanf("%lf", &new_profile.max_distance);

    printf("Select a transport option>\n");
    for (int i = 0; i < TRANSPORT_OPTIONS; i++) {
        printf("[%d] %s\n", i, string_from_enum_transport(i));
    }
    scanf("%d", &new_profile.transport);

    printf("Select a username> ");
    scanf("%s", new_profile.username);

    printf("Select a password> ");
    scanf("%s", new_profile.password);

    return new_profile;
}

t_user_profile load_profile(FILE *file, char *file_name, int id) {
    file = fopen(file_name, "r");

    validate_file_pointer(file);

    t_user_profile new_profile;

    do {
        fscanf(file, "%d %s %s %s %s %lf %lf %lf %d %u",
               &new_profile.id, new_profile.name, new_profile.address, new_profile.username, new_profile.password,
               &new_profile.longitude, &new_profile.latitude, &new_profile.max_distance, &new_profile.age,
               &new_profile.transport);
    } while (new_profile.id != id);

    fclose(file);

    return new_profile;
}

void upload_profile(FILE *file, char *file_name, t_user_profile profile, t_user_profile database[]) {
    file = fopen(file_name, "a");

    validate_file_pointer(file);

    if (!validate_credentials_in_database(file, file_name, profile.username, profile.password, database, NULL, false))
        fprintf(file, "%d %s %s %s %s %lf %lf %f %d %u\n", profile.id, profile.name, profile.address, profile.username,
                profile.password,
                profile.longitude, profile.latitude, profile.max_distance, profile.age, profile.transport);

    fclose(file);
}

t_user_profile *load_database(FILE *file, char *file_name) {
    int lines_in_file = count_lines_in_file(file, file_name);

    t_user_profile *database = malloc(lines_in_file * sizeof(*database));

    for (int i = 0; i < lines_in_file; i++) {
        database[i] = load_profile(file, file_name, i);
    }

    return database;
}