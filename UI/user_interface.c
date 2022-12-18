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
t_function_table FunctionTable[] =
        {
                {0, "login_window",    login_window},
                {1, "register_window", register_window}
        };

void initialise_ui(float WIDTH, float HEIGHT) {
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

    if (!InitWindow.initialised) {
        igStyleColorsDark(NULL);
        load_styles();

        WindowSettings.size = MAIN_FRAME;
        WindowSettings.size_cond = ImGuiCond_Once;
        WindowSettings.pos = CENTER_POS;
        WindowSettings.pos_cond = ImGuiCond_Always;
        WindowSettings.child_size = MAIN_CHILD_FRAME;
        WindowSettings.windowflags = window_flags;

        InitWindow.initialised = !InitWindow.initialised;
    }

    igSetNextWindowPos(CENTER_POS, ImGuiCond_Always, Vec2(0.5f, 0.5f));
    igSetNextWindowSize(MAIN_FRAME, ImGuiCond_Once);

    igBegin("initial ui", 0, window_flags);
    igPushStyleVar_Float(ImGuiStyleVar_ChildRounding, 100.f);
    {

        igSetNextWindowPos(CENTER_POS, ImGuiCond_Always, Vec2(0.5f, 0.5f));
        igBeginChildFrame(1, MAIN_CHILD_FRAME, ImGuiWindowFlags_ChildWindow);
        {

            igSetCursorPos(Vec2(115, 35));
            igText("Please select an option");

            igSetCursorPos(Vec2(25, 75));
            if (igButton("Login", Vec2(350, 50))) {
                ActiveWindow.render_login = true;
                update_program_settings(&ActiveWindow, &ProgramStatus, 0, true, true);
            }

            igSetCursorPos(Vec2(25, 130));
            if (igButton("Register", Vec2(350, 50))) {
                ActiveWindow.render_registration = true;
                update_program_settings(&ActiveWindow, &ProgramStatus, 1, true, true);
            }
        }
        igEndChildFrame();
    }
    igPopStyleVar(1);
    igEnd();


    if (ProgramStatus.current_active_window_status && ProgramStatus.current_window_settings_status) {
        run_new_window(WindowSettings, current_active_window(FunctionTable, ProgramStatus.current_active_window_id));
    }
}

void login_window() {
    igSetCursorPos(Vec2(25, 150));
    if (igButton("Login", Vec2(350, 50))) {
        printf("Logged in!\n");
    }

    igSetCursorPos(Vec2(150, 220));
    if (igButton("<-", Vec2(100, 25))) {
        update_program_settings(&ActiveWindow, &ProgramStatus, -1, false, false);
    }
}

void register_window() {
    igSetCursorPos(Vec2(25, 150));
    if (igButton("Register", Vec2(350, 50))) {
        printf("Registered!\n");
    }

    igSetCursorPos(Vec2(150, 220));
    if (igButton("<-", Vec2(100, 25))) {
        update_program_settings(&ActiveWindow, &ProgramStatus, -1, false, false);
    }
}
