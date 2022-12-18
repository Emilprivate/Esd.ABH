#include <stdbool.h>

#ifndef CIMGUI_SOKOL_STARTERKIT_USER_INTERFACE_H
#define CIMGUI_SOKOL_STARTERKIT_USER_INTERFACE_H

#endif //CIMGUI_SOKOL_STARTERKIT_USER_INTERFACE_H

void initialise_ui(int WIDTH, int HEIGHT);

typedef struct active_window_struct{
    bool render_login;
    bool render_registration;
    bool render_main_menu;
    bool render_view_profile;
    bool render_view_cart;
    bool render_settings;
    bool render_search;

}t_active_window;

// ImVec2 size, ImGuiCond size_cond, ImVec2 pos, ImGuiCond pos_cond, ImGuiWindowFlags windowflags
typedef struct new_window_struct{
    bool init;
    ImVec2 size;
    ImGuiCond size_cond;
    ImVec2 pos;
    ImGuiCond pos_cond;
    ImVec2 child_size;
    ImGuiWindowFlags windowflags;
}t_new_window;

typedef struct program_status{
    bool current_active_window_exists;
    bool windows_settings_updated;
    int current_active_window_id;
    bool logout;
    bool quit_program;
}t_program_status;

typedef struct debug_ui_interaction_struct{
    bool render_demo_window;
    bool render_debuglog_window;
}t_debug_window;

typedef struct init_control_struct{
    bool initialised;
    bool init_ui_status;
}t_init_window;