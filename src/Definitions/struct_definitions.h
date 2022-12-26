#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include <sys/time.h>
#include "cimgui.h"

#ifndef P1_EXTENSION_STRUCT_DEFINITIONS_H
#define P1_EXTENSION_STRUCT_DEFINITIONS_H

#include "enum_definitions.h"

#define MAX 32

typedef struct user_profile_struct {
    int id;
    char name[MAX];
    char address[MAX];
    char username[MAX];
    char password[MAX];
    double longitude;
    double latitude;
    double max_distance;
    int age;
    e_transport transport;
} t_user_profile;

typedef struct login_user_struct {
    bool init;
    char temp_username[MAX];
    char temp_password[MAX];
} t_login_user;

typedef struct session_struct {
    bool init_login;
    time_t login_time;
    time_t logout_time;
    time_t session_time;
    time_t live_time;
} t_session;

typedef struct init_file_struct {
    FILE *file;
    char *file_name;
} t_init_file;

typedef struct program_status_struct {
    int current_active_window_id;
    char *output_status;
    bool logout;
    bool quit_program;
} t_program_status;

typedef struct new_window_struct {
    float WIDTH;
    float HEIGHT;
    ImVec2 size;
    ImGuiCond size_cond;
    ImVec2 pos;
    ImGuiCond pos_cond;
    ImVec2 child_size;
    ImGuiWindowFlags windowflags;
} t_new_window;

//To make the windows dynamic to size (a lot of math, cba)
typedef struct new_button_struct {

} t_new_button;

typedef struct init_control_struct {
    bool initialised;
} t_init_window;

typedef struct function_table_struct {
    const int id;
    const char *name;

    void (*func)(void);
} t_function_table;

typedef struct debug_ui_interaction_struct {
    bool render_demo_window;
    bool render_debuglog_window;
} t_debug_window;

#endif //P1_EXTENSION_STRUCT_DEFINITIONS_H
