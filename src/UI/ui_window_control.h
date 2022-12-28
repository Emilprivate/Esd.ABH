#ifndef P1_EXTENSION_WINDOW_NAVIGATION_CONTROL_H
#define P1_EXTENSION_WINDOW_NAVIGATION_CONTROL_H

//External prototypes
void run_new_window(t_new_window newWindowInfo, void callActiveWindow());

void update_window_settings(t_program_status *program, t_new_window *window_settings, int id);

void *current_active_window(t_function_table functionTable[], int id);

#endif //P1_EXTENSION_WINDOW_NAVIGATION_CONTROL_H