#include <stdbool.h>

#ifndef P1_EXTENSION_WINDOW_NAVIGATION_CONTROL_H
#define P1_EXTENSION_WINDOW_NAVIGATION_CONTROL_H

#endif //P1_EXTENSION_WINDOW_NAVIGATION_CONTROL_H

typedef struct active_window_struct{
    bool render_login;
    bool render_registration;
    bool render_view_profile;
    bool render_view_cart;
    bool render_settings;
    bool render_search;

}t_active_window;

typedef struct program_status_struct{
    int current_active_window_id;
    bool logout;
    bool quit_program;
}t_program_status;

typedef struct new_window_struct{
    ImVec2 size;
    ImGuiCond size_cond;
    ImVec2 pos;
    ImGuiCond pos_cond;
    ImVec2 child_size;
    ImGuiWindowFlags windowflags;
}t_new_window;

typedef struct init_control_struct{
    bool initialised;
}t_init_window;

typedef struct function_table_struct {
    const int id;
    const char *name;

    void (*func)(void);
} t_function_table;

//External prototypes
void run_new_window(t_new_window newWindowInfo, void callActiveWindow());
void update_program_settings(t_active_window *window, t_program_status *program, int id, bool go_back);
void update_window_status(t_active_window *activeWindow, t_program_status *program, int id);
void *current_active_window(t_function_table functionTable[], int id);