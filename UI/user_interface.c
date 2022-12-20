#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "../Libraries/cimgui/cimgui.h"
#include "../utilities.h"

#include "user_interface.h"
#include "window_navigation_control.h"

//Struct initialisations
t_init_window InitWindow;
t_active_window ActiveWindow;
t_program_status ProgramStatus;
t_new_window WindowSettings;
t_login_user LoginUser;
t_init_file InitFile;

t_function_table FunctionTable[] ={
                {0, "initialise_window", initialise_window},
                {1, "main_window", 0},
                {2, "login_window", login_window},
                {3, "register_window", register_window}
        };

void initialise_ui(float WIDTH, float HEIGHT)
{
    ImVec2 MAIN_FRAME = Vec2(WIDTH, HEIGHT);
    ImVec2 CENTER_POS = Vec2(WIDTH * 0.5f, HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(400, 250);

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
    window_flags |= ImGuiWindowFlags_NoSavedSettings;
    window_flags |= ImGuiWindowFlags_NoInputs;

    if (!InitWindow.initialised)
    {
        igStyleColorsDark(NULL);
        load_styles();

        WindowSettings.size = MAIN_FRAME;
        WindowSettings.size_cond = ImGuiCond_Once;
        WindowSettings.pos = CENTER_POS;
        WindowSettings.pos_cond = ImGuiCond_Always;
        WindowSettings.child_size = MAIN_CHILD_FRAME;
        WindowSettings.windowflags = window_flags;

        ProgramStatus.current_active_window_id = 0;

        InitFile.file_name = "Userprofiles.txt";
        InitFile.file = NULL;

        InitWindow.initialised = !InitWindow.initialised;
    }

    run_new_window(WindowSettings, current_active_window(FunctionTable, ProgramStatus.current_active_window_id));
}

void initialise_window()
{
    igSetCursorPos(Vec2(115, 35));
    igText("Please select an option");

    igSetCursorPos(Vec2(25, 75));
    if (igButton("Login", Vec2(350, 50)))
    {
        ActiveWindow.render_login = true;
        update_window_status(&ActiveWindow, &ProgramStatus, 2);
    }

    igSetCursorPos(Vec2(25, 130));
    if (igButton("Register", Vec2(350, 50)))
    {
        ActiveWindow.render_registration = true;
        update_window_status(&ActiveWindow, &ProgramStatus, 3);
    }
}

void login_window()
{

    igSetCursorPos(Vec2(35, 30));
    igText("Username");
    igSetCursorPos(Vec2(35, 50));
    igInputText("##", LoginUser.temp_username, 64, 0, NULL, NULL);

    igSetCursorPos(Vec2(35, 80));
    igText("Password");
    igSetCursorPos(Vec2(35, 100));
    igInputText("##", LoginUser.temp_password, 64, 0, NULL, NULL);

    igSetCursorPos(Vec2(25, 150));
    if (igButton("Login", Vec2(350, 50)))
    {
        // TODO: Login backend
    }

    igSetCursorPos(Vec2(150, 220));
    if (igButton("<-", Vec2(100, 25)))
    {
        update_window_status(&ActiveWindow, &ProgramStatus, 0);
    }


}

void register_window()
{
    igSetCursorPos(Vec2(25, 150));
    if (igButton("Register", Vec2(350, 50)))
    {
        // TODO: Register backend
        int id = count_lines_in_file(InitFile.file, InitFile.file_name);

    }

    igSetCursorPos(Vec2(150, 220));
    if (igButton("<-", Vec2(100, 25)))
    {
        update_window_status(&ActiveWindow, &ProgramStatus, 0);
    }
}
