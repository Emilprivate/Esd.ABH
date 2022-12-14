#include <stdbool.h>

#ifndef CIMGUI_SOKOL_STARTERKIT_USER_INTERFACE_H
#define CIMGUI_SOKOL_STARTERKIT_USER_INTERFACE_H

#endif //CIMGUI_SOKOL_STARTERKIT_USER_INTERFACE_H

void initialise_ui(int WIDTH, int HEIGHT);

typedef struct main_ui_interaction_struct{
    bool render_login;
    bool render_registration;
    bool quit_program;
}t_m_uii;

typedef struct session_ui_interaction_struct{
    bool render_view_profile;
    bool render_view_cart;
    bool render_settings;
    bool render_search;
    bool logout;
}t_s_uii;

typedef struct debug_ui_interaction_struct{
    bool render_demo_window;
    bool render_debuglog_window;
}t_d_uii;

typedef struct init_control_struct{
    bool initialised;
}t_i_cs;