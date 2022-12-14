#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "terminal_debug_menu.h"
#include "utilities.h"

#define MAX 30

void main_menu(t_user_profile profile, time_t login_time);
void login_page(FILE * file, char * file_name);
void registration_page(FILE * file, char * file_name);
void view_profile_page(t_user_profile profile, time_t session);
void view_cart_page(t_user_profile profile, time_t session);
void clear_screen();

void initial_screen()
{
    int choice;

    FILE * file = NULL;
    char * file_name = "Userprofiles.txt";

    printf("1) Login\n");
    printf("2) Register\n");
    printf("3) Exit\n");
    scanf("%d", &choice);
    clear_screen();

    switch(choice)
    {
        case 1:
            login_page(file, file_name);
            break;
        case 2:
            registration_page(file, file_name);
            break;
        case 3:
            printf("Goodbye!\n");
            exit(EXIT_SUCCESS);
        default:
            printf("\n");
            initial_screen();
    }
}

void main_menu(t_user_profile profile, time_t login_time)
{
    int choice;

    time_t logout_time, session;

    printf("----------------------------------------\n");
    printf("Session started at %s\n", ctime(&login_time));
    printf("Prototype | Welcome %s\n", profile.name);
    printf("1) View your profile\n");
    printf("2) View your cart\n");
    printf("3) Search\n");
    printf("4) Logout\n");
    scanf("%d", &choice);
    clear_screen();

    switch(choice)
    {
        case 1:
            view_profile_page(profile, login_time);
            break;
        case 2:
            view_cart_page(profile, login_time);
            break;
        case 3:
            break;
        case 4:
            time(&logout_time);
            session = logout_time - login_time;

            printf("Previous session started at %s", ctime(&login_time));
            printf("Previous session ended at %s", ctime(&logout_time));

            session_time_calculator(session);

            initial_screen();
            break;
        default:
            main_menu(profile, login_time);
    }
}

void login_page(FILE * file, char * file_name)
{
    clear_screen();
    char temp_username[MAX];
    char temp_password[MAX];

    time_t login_time;

    t_user_profile * database = load_database(file, file_name);

    printf("Please enter your username> \n");
    scanf("%s", temp_username);

    printf("Please enter your password> \n");
    scanf("%s", temp_password);

    int id = 0;
    if (!validate_credentials_in_database(file, file_name, temp_username, temp_password, database, &id, true)){
        clear_screen();
        printf("Login failed, please check your credentials and try again\n");
        initial_screen();
    }
    clear_screen();

    time(&login_time);
    main_menu(database[id], login_time);
}

void registration_page(FILE * file, char * file_name)
{
    clear_screen();
    t_user_profile * database = load_database(file, file_name);

    int id = count_lines_in_file(file, file_name);
    t_user_profile new_profile = create_profile(id);

    upload_profile(file, file_name, new_profile, database);

    printf("Successfully created a profile!\n\n");
    initial_screen();
}

void view_profile_page(t_user_profile profile, time_t session)
{
    int choice;

    printf("Profile overview\n");
    printf("------------------------------------------------------\n");
    printf("ID: %d | Name: %s | Age: %d\n", profile.id, profile.name, profile.age);
    printf("Username: %s | Password: %s\n", profile.username, profile.password);
    printf("Address: %s | Longitude: %lf | Latitude: %lf\n", profile.address, profile.longitude, profile.latitude);
    printf("Transport: %s | Max travel distance: %f\n", string_from_enum_transport(profile.transport), profile.max_distance);
    printf("------------------------------------------------------\n");
    printf("1) Back\n");
    scanf("%d", &choice);

    if (choice == 1){
        clear_screen();
        main_menu(profile, session);
    }
}

void view_cart_page(t_user_profile profile, time_t session){
    FILE * file = fopen("Cartlist.txt", "r");
    validate_file_pointer(file);

    int choice;
    char product_name[MAX];

    for (int i = 0; i < count_lines_in_file(file, "Cartlist.txt"); i++){
        fscanf(file, "%s", product_name);
        printf("Product [%d]: %s\n", i, product_name);
    }
    fclose(file);
    printf("------------------------------------------------------\n");
    printf("1) Back\n");
    scanf("%d", &choice);

    if (choice == 1) {
        clear_screen();
        main_menu(profile, session);
    }
}

void clear_screen(){
    for (int i = 0; i < 20; i++){
        printf("\n");
    }
}