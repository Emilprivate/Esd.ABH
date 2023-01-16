#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "../Definitions/struct_definitions.h"
#include "../Header/utilities.h"
#include "ui_window_design.h"
#include "ui_window_control.h"
#include "ui_window_settings.h"

void run_new_window(t_new_window newWindowInfo, void callActiveWindow()) {
    igSetNextWindowPos(newWindowInfo.pos, newWindowInfo.pos_cond, Vec2(0.5f, 0.5f));
    igSetNextWindowSize(newWindowInfo.size, newWindowInfo.size_cond);

    igBegin("##new_window", 0, newWindowInfo.windowflags);
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

void update_window_settings(t_program_status *program, t_new_window *window_settings, int id) {
    update_output_status(program, "...");
    program->current_active_window_id = id;

    switch (id) {
        case 0:
            initialise_initial_window_settings(window_settings);
            break;
        case 1:
            initialise_main_window_settings(window_settings);
            break;
        case 2:
            initialise_login_window_settings(window_settings);
            break;
        case 3:
            initialise_registration_window_settings(window_settings);
            break;
        case 4:
            initialise_view_profile_window_settings(window_settings);
            break;
        case 5:
            initialise_view_cart_window_settings(window_settings);
            break;
        case 6:
            initialise_search_window_settings(window_settings);
            break;
        case 7:
            initialise_settings_window_settings(window_settings);
            break;
        default:
            default_window_settings(window_settings);
    }
}