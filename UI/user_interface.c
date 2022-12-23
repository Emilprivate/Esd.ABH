#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "../Libraries/cimgui/cimgui.h"
#include "../utilities.h"

#include "user_interface.h"
#include "..\user_operations.h"

//Internal prototypes
void initial_window();
void login_window();
void register_window();
void main_window();


//Struct initialisations
t_init_window    InitWindow;
t_program_status ProgramStatus;
t_new_window     WindowSettings;
t_login_user     LoginUser;
t_init_file      InitFile;
t_user_profile   UserProfile;
t_function_table FunctionTable[] ={
                {0, "initial_window",  initial_window},
                {1, "main_window",     main_window},
                {2, "login_window",    login_window},
                {3, "register_window", register_window}
        };

void initialise_ui(float WIDTH, float HEIGHT)
{

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

        InitFile.file_name = "Userprofiles.txt";
        InitFile.file = NULL;

        WindowSettings.WIDTH = WIDTH;
        WindowSettings.HEIGHT = HEIGHT;

        initialise_initial_login_window_settings(WIDTH, HEIGHT, window_flags);

        update_window_status(&ProgramStatus, WindowSettings, 0);

        InitWindow.initialised = !InitWindow.initialised;
    }

    run_new_window(WindowSettings, current_active_window(FunctionTable, ProgramStatus.current_active_window_id));
}

void initial_window()
{
    igSetCursorPos(Vec2(115, 35));
    igText("Please select an option");

    igSetCursorPos(Vec2(25, 75));
    if (igButton("Login", Vec2(350, 50)))
    {
        update_window_status(&ProgramStatus, WindowSettings, 2);
    }

    igSetCursorPos(Vec2(25, 130));
    if (igButton("Register", Vec2(350, 50)))
    {
        update_window_status(&ProgramStatus, WindowSettings, 3);
    }
}

void main_window()
{
    igSetCursorPos(Vec2(115, 35));
    igText("Welcome to the main window");

    igSetCursorPos(Vec2(25, 75));
    if (igButton("Logout", Vec2(350, 50)))
    {
        update_window_status(&ProgramStatus, WindowSettings, 0);
    }
}

void login_window()
{
    igSetCursorPos(Vec2(25, 230));
    igText("Status: %s", ProgramStatus.output_status != NULL ? ProgramStatus.output_status : "...");

    igSetCursorPos(Vec2(68, 50));
    igText("Username");

    igSetCursorPos(Vec2(68, 70));
    igInputText(" ", LoginUser.temp_username, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igSetCursorPos(Vec2(68, 100));
    igText("Password");

    igSetCursorPos(Vec2(68, 120));
    igInputText("  ", LoginUser.temp_password, MAX, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igSetCursorPos(Vec2(25, 175));
    if (igButton("Login", Vec2(350, 50)))
    {
        if (login_operation(InitFile.file, InitFile.file_name, LoginUser))
        {
            update_window_status(&ProgramStatus, WindowSettings, 1);
        }
        else
        {
            update_output_status(&ProgramStatus, "Failed to login!");
        }
    }

    igSetCursorPos(Vec2(5, 5));
    if (igButton("<", Vec2(25, 25)))
    {
        update_window_status(&ProgramStatus, WindowSettings, 0);
    }
}

void register_window()
{
    igSetCursorPos(Vec2(25, 300));
    igText("Status: %s", ProgramStatus.output_status != NULL ? ProgramStatus.output_status : "...");

    igPushItemWidth(-200);

    //-----------------LEFT PANEL-----------------//

    igSetCursorPos(Vec2(25, 40));
    igText("Name");

    igSetCursorPos(Vec2(25, 60));
    igInputText(" ", UserProfile.name, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    //----------------------------------------------------------------------------------

    igSetCursorPos(Vec2(25, 90));
    igText("Address");

    igSetCursorPos(Vec2(25, 110));
    igInputText("  ", UserProfile.address, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    //----------------------------------------------------------------------------------

    igSetCursorPos(Vec2(25, 140));
    igText("Username");

    igSetCursorPos(Vec2(25, 160));
    igInputText("   ", UserProfile.username, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    //----------------------------------------------------------------------------------

    igSetCursorPos(Vec2(25, 190));
    igText("Password");

    igSetCursorPos(Vec2(25, 210));
    igInputText("    ", UserProfile.password, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    //----------------------------------------------------------------------------------

    igPopItemWidth();

    igPushItemWidth(-20);

    //-----------------RIGHT PANEL-----------------//

    igSetCursorPos(Vec2(200, 40));
    igText("Age");

    igSetCursorPos(Vec2(200, 60));
    igInputScalar("     ", ImGuiDataType_U8, &UserProfile.age, NULL, NULL, NULL, ImGuiInputTextFlags_CharsDecimal);

    //----------------------------------------------------------------------------------

    igSetCursorPos(Vec2(200, 90));
    igText("Longitude");

    igSetCursorPos(Vec2(200, 110));
    igInputScalar("      ", ImGuiDataType_Double, &UserProfile.longitude, NULL, NULL, NULL, ImGuiInputTextFlags_CharsDecimal);
    //----------------------------------------------------------------------------------

    igSetCursorPos(Vec2(200, 140));
    igText("Latitude");

    igSetCursorPos(Vec2(200, 160));
    igInputScalar("       ", ImGuiDataType_Double, &UserProfile.latitude, NULL, NULL, NULL, ImGuiInputTextFlags_CharsDecimal);

    //----------------------------------------------------------------------------------

    igSetCursorPos(Vec2(200, 190));
    igText("Max traveling distance");

    igSetCursorPos(Vec2(200, 210));
    igInputScalar("        ", ImGuiDataType_Double, &UserProfile.max_distance, NULL, NULL, NULL, ImGuiInputTextFlags_CharsDecimal);

    //----------------------------------------------------------------------------------

    igPopItemWidth();

    igSetCursorPos(Vec2(25, 245));
    if (igButton("Register", Vec2(350, 50)))
    {
        if (registration_operation(InitFile.file, InitFile.file_name, UserProfile))
        {
            update_output_status(&ProgramStatus, "Successfully registered!");
        }else
        {
            update_output_status(&ProgramStatus, "Failed to register!");
        }
    }

    igSetCursorPos(Vec2(5, 5));
    if (igButton("<", Vec2(25, 25)))
    {
        update_window_status(&ProgramStatus, WindowSettings, 0);
    }
}

void initialise_initial_login_window_settings(float WIDTH, float HEIGHT, ImGuiWindowFlags window_flags)
{
    ImVec2 MAIN_FRAME = Vec2(WIDTH, HEIGHT);
    ImVec2 CENTER_POS = Vec2(WIDTH * 0.5f, HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(400, 250);

    WindowSettings.size = MAIN_FRAME;
    WindowSettings.size_cond = ImGuiCond_Once;
    WindowSettings.pos = CENTER_POS;
    WindowSettings.pos_cond = ImGuiCond_Always;
    WindowSettings.child_size = MAIN_CHILD_FRAME;
    WindowSettings.windowflags = window_flags;
}

void initialise_main_window_settings(float WIDTH, float HEIGHT, ImGuiWindowFlags window_flags)
{
    ImVec2 CENTER_POS = Vec2(WIDTH * 0.5f, HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(600, 400);

    WindowSettings.pos = CENTER_POS;
    WindowSettings.pos_cond = ImGuiCond_Always;
    WindowSettings.child_size = MAIN_CHILD_FRAME;
    WindowSettings.windowflags = window_flags;
}

void initialise_registration_window_settings(float WIDTH, float HEIGHT, ImGuiWindowFlags window_flags)
{
    ImVec2 CENTER_POS = Vec2(WIDTH * 0.5f, HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(400, 320);

    WindowSettings.pos = CENTER_POS;
    WindowSettings.pos_cond = ImGuiCond_Always;
    WindowSettings.child_size = MAIN_CHILD_FRAME;
    WindowSettings.windowflags = window_flags;
}
