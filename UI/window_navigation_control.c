#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "../Libraries/cimgui/cimgui.h"
#include "../utilities.h"

#include "user_interface.h"

void run_new_window(t_new_window newWindowInfo, void callActiveWindow())
{
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

void *current_active_window(t_function_table functionTable[], int id)
{
    return functionTable[id].func;
}

void update_window_status(t_program_status *program, t_new_window window_settings, int id)
{
    update_output_status(program, "...");
    program->current_active_window_id = id;

    switch(id){
        case 1:
            initialise_main_window_settings(window_settings.WIDTH, window_settings.HEIGHT, window_settings.windowflags);
            break;
        case 3:
            initialise_registration_window_settings(window_settings.WIDTH, window_settings.HEIGHT,window_settings.windowflags);
            break;
        default:
            initialise_initial_login_window_settings(window_settings.WIDTH, window_settings.HEIGHT, window_settings.windowflags);
    }
}