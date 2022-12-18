#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "../Libraries/cimgui/cimgui.h"
#include "../utilities.h"

#include "user_interface.h"
#include "window_navigation_control.h"

void run_new_window(t_new_window newWindowInfo, void callActiveWindow()) {
    igSetNextWindowPos(newWindowInfo.pos, newWindowInfo.pos_cond, Vec2(0.5f, 0.5f));
    igSetNextWindowSize(newWindowInfo.size, newWindowInfo.size_cond);

    igBegin(" ", 0, newWindowInfo.windowflags);
    igPushStyleVar_Float(ImGuiStyleVar_ChildRounding, 100.f);
    {

        igSetNextWindowPos(newWindowInfo.pos, newWindowInfo.pos_cond, Vec2(0.5f, 0.5f));
        igBeginChildFrame(1, newWindowInfo.child_size, ImGuiWindowFlags_ChildWindow);
        {
            callActiveWindow();
        }
        igEndChildFrame();


    }
    igPopStyleVar(1);
    igEnd();
}

void *current_active_window(t_function_table functionTable[], int id) {
    return functionTable[id].func;
}

void update_window_status(t_active_window *activeWindow, int id) {
    printf("Updating window statuses...\n");
    for (int j = 0; j < sizeof(activeWindow) / sizeof(bool); j++) {
        if (id != j) {
            ((bool *) &activeWindow)[j] = false;
        }
    }
    printf("Updated window status!\n");
}

void update_program_settings(t_active_window *window, t_program_status *program, int id,
                             bool window_status, bool settings_status) {
    printf("Updating program settings...\n");

    program->current_active_window_id = id;
    program->current_active_window_status = window_status;
    program->current_window_settings_status = settings_status;

    update_window_status(window, program->current_active_window_id);

    printf("Updated program settings!\n");
}