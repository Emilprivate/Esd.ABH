#include <stdbool.h>

#ifndef P1_EXTENSION_USER_INTERFACE_H
#define P1_EXTENSION_USER_INTERFACE_H

#endif //P1_EXTENSION_USER_INTERFACE_H

//External prototypes
void initialise_ui(float WIDTH, float HEIGHT);
void initialise_registration_window_settings(float WIDTH, float HEIGHT, ImGuiWindowFlags window_flags);
void initialise_initial_login_window_settings(float WIDTH, float HEIGHT, ImGuiWindowFlags window_flags);
void initialise_main_window_settings(float WIDTH, float HEIGHT, ImGuiWindowFlags window_flags);

typedef struct debug_ui_interaction_struct{
    bool render_demo_window;
    bool render_debuglog_window;
}t_debug_window;

