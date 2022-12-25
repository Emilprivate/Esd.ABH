#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS


#include "cimgui.h"
#include "../../Definitions/struct_definitions.h"
#include "../../Header/user_operations.h"
#include "../../Header/utilities.h"

#include "../Header/window_navigation_control.h"
#include "../Header/user_interface.h"
#include "../Header/ui_window_settings.h"

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
t_session        Session;
t_user_profile   RegisterUserProfile;
t_user_profile   LoginUserProfile;

t_function_table FunctionTable[] ={
                {0, "initial_window",  initial_window},
                {1, "main_window",     main_window},
                {2, "login_window",    login_window},
                {3, "register_window", register_window}
        };

void initialise_ui(float WIDTH, float HEIGHT)
{

    if (!InitWindow.initialised)
    {
        igStyleColorsDark(NULL);
        load_styles();

        InitFile.file_name = "Userprofiles.txt";
        InitFile.file = NULL;

        WindowSettings.WIDTH = WIDTH;
        WindowSettings.HEIGHT = HEIGHT;

        WindowSettings.windowflags = 0;
        WindowSettings.windowflags |= ImGuiWindowFlags_NoTitleBar;
        WindowSettings.windowflags |= ImGuiWindowFlags_NoResize;
        WindowSettings.windowflags |= ImGuiWindowFlags_NoMove;
        WindowSettings.windowflags |= ImGuiWindowFlags_NoCollapse;
        WindowSettings.windowflags |= ImGuiWindowFlags_NoScrollbar;
        WindowSettings.windowflags |= ImGuiWindowFlags_NoScrollWithMouse;
        WindowSettings.windowflags |= ImGuiWindowFlags_NoSavedSettings;
        WindowSettings.windowflags |= ImGuiWindowFlags_NoInputs;

        initialise_initial_window_settings(&WindowSettings);

        update_window_settings(&ProgramStatus, &WindowSettings, 0);

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
        update_window_settings(&ProgramStatus, &WindowSettings, 2);
    }

    igSetCursorPos(Vec2(25, 130));
    if (igButton("Register", Vec2(350, 50)))
    {
        update_window_settings(&ProgramStatus, &WindowSettings, 3);
    }
}

void main_window()
{
    igSetCursorPos(Vec2(igGetWindowWidth() * 0.5f - 175, igGetWindowHeight() * 0.5f - 125));
    igBeginGroup();

    time(&Session.live_time);

    igText("Welcome %s | Session: %s", LoginUserProfile.name, ctime(&Session.live_time));
    igNewLine();

    if (igButton("View profile", Vec2(350, 50)))
    {

    }

    if (igButton("View cart", Vec2(350, 50)))
    {

    }

    if (igButton("Search items", Vec2(350, 50)))
    {

    }

    if (igButton("Settings", Vec2(350, 50)))
    {

    }

    if (igButton("Logout", Vec2(350, 50)))
    {
        time(&Session.logout_time);
        printf("Session ended at: %s\n", ctime(&Session.logout_time));

        Session.session_time = Session.logout_time - Session.login_time;
        session_time_calculator(Session.session_time);

        update_window_settings(&ProgramStatus, &WindowSettings, 2);
    }

    igEndGroup();
}

void login_window()
{
    igSetCursorPos(Vec2(68, 50));
    igBeginGroup();

    igText("Username");
    igInputText("##login_username", LoginUser.temp_username, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igText("Password");
    igInputText("##login_password", LoginUser.temp_password, MAX, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igEndGroup();

    igSetCursorPos(Vec2(25, 230));
    igText("Status: %s", ProgramStatus.output_status != NULL ? ProgramStatus.output_status : "...");

    igSetCursorPos(Vec2(25, 175));
    if (igButton("Login", Vec2(350, 50)))
    {
        if (login_operation(InitFile.file, InitFile.file_name, LoginUser, &LoginUserProfile))
        {
            time(&Session.login_time);
            update_window_settings(&ProgramStatus, &WindowSettings, 1);
        }
        else
        {
            update_output_status(&ProgramStatus, "Failed to login!");
        }
    }

    igSetCursorPos(Vec2(5, 5));
    if (igButton("<", Vec2(25, 25)))
    {
        update_window_settings(&ProgramStatus, &WindowSettings, 0);
    }
}

void register_window()
{
    //-----------------LEFT PANEL-----------------//
    igPushItemWidth(-200);
    igSetCursorPos(Vec2(25, 40));
    igBeginGroup();

    igText("Name");
    igInputText("##name", RegisterUserProfile.name, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igText("Address");
    igInputText("##address", RegisterUserProfile.address, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igText("Username");
    igInputText("##register_username", RegisterUserProfile.username, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igText("Password");
    igInputText("##register_password", RegisterUserProfile.password, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igEndGroup();
    igPopItemWidth();


    //-----------------RIGHT PANEL-----------------//
    igPushItemWidth(-20);
    igSetCursorPos(Vec2(200, 40));
    igBeginGroup();

    igText("Age");
    igInputScalar("##age", ImGuiDataType_U8, &RegisterUserProfile.age, NULL, NULL, NULL, ImGuiInputTextFlags_CharsDecimal);

    igText("Longitude");
    igInputScalar("##longitude", ImGuiDataType_Double, &RegisterUserProfile.longitude, NULL, NULL, NULL, ImGuiInputTextFlags_CharsDecimal);

    igText("Latitude");
    igInputScalar("##latitude", ImGuiDataType_Double, &RegisterUserProfile.latitude, NULL, NULL, NULL, ImGuiInputTextFlags_CharsDecimal);

    igText("Max traveling distance");
    igInputScalar("##max_traveling_distance", ImGuiDataType_Double, &RegisterUserProfile.max_distance, NULL, NULL, NULL, ImGuiInputTextFlags_CharsDecimal);

    igEndGroup();
    igPopItemWidth();

    igSetCursorPos(Vec2(25, 300));
    igText("Status: %s", ProgramStatus.output_status != NULL ? ProgramStatus.output_status : "...");

    igSetCursorPos(Vec2(25, 245));
    if (igButton("Register", Vec2(350, 50)))
    {
        if (registration_operation(InitFile.file, InitFile.file_name, RegisterUserProfile))
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
        update_window_settings(&ProgramStatus, &WindowSettings, 0);
    }
}
