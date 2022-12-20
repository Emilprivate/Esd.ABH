#include <stdbool.h>

#ifndef P1_EXTENSION_USER_INTERFACE_H
#define P1_EXTENSION_USER_INTERFACE_H

#endif //P1_EXTENSION_USER_INTERFACE_H

//External prototypes
void initialise_ui(float WIDTH, float HEIGHT);
void initialise_window();
void login_window();
void register_window();

typedef struct debug_ui_interaction_struct{
    bool render_demo_window;
    bool render_debuglog_window;
}t_debug_window;

