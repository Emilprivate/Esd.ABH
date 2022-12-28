#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "cimgui.h"
#include "../Definitions/struct_definitions.h"
#include "../Header/user_operations.h"
#include "../Header/utilities.h"

#include "ui_window_control.h"
#include "ui_window_design.h"
#include "ui_window_settings.h"

//Internal prototypes
void initial_window();
void main_window();
void login_window();
void register_window();
void view_profile_window();
void view_cart_window();
void search_window();
void settings_window();

//Struct initialisations
t_init_window initWindow;
t_program_status programStatus;
t_new_window windowSettings;
t_login_user loginUser;
t_init_file initFile;
t_session session;
t_user_profile registerUserProfile;
t_user_profile loginUserProfile;

t_function_table functionTable[] = {
        {0, "initial_window",  initial_window},
        {1, "main_window",     main_window},
        {2, "login_window",    login_window},
        {3, "register_window", register_window},
        {4, "view_profile_window", view_profile_window},
        {5, "view_cart_window", view_cart_window},
        {6, "search_window", search_window},
        {7, "settings_window", settings_window}
};

void initialise_ui(float WIDTH, float HEIGHT)
{
    if (!initWindow.initialised)
    {
        igStyleColorsCustom(NULL);
        //igStyleColorsDark(NULL);

        initFile.file_name = "Userprofiles.txt";
        initFile.file = NULL;

        windowSettings.WIDTH = WIDTH;
        windowSettings.HEIGHT = HEIGHT;

        windowSettings.windowflags = 0;
        windowSettings.windowflags |= ImGuiWindowFlags_NoTitleBar;
        windowSettings.windowflags |= ImGuiWindowFlags_NoResize;
        windowSettings.windowflags |= ImGuiWindowFlags_NoMove;
        windowSettings.windowflags |= ImGuiWindowFlags_NoCollapse;
        windowSettings.windowflags |= ImGuiWindowFlags_NoScrollbar;
        windowSettings.windowflags |= ImGuiWindowFlags_NoScrollWithMouse;
        windowSettings.windowflags |= ImGuiWindowFlags_NoSavedSettings;
        windowSettings.windowflags |= ImGuiWindowFlags_NoInputs;

        initialise_initial_window_settings(&windowSettings);

        update_window_settings(&programStatus, &windowSettings, 1);

        initWindow.initialised = !initWindow.initialised;
    }

    run_new_window(windowSettings, current_active_window(functionTable, programStatus.current_active_window_id));
}

void initial_window()
{
    igSetCursorPos(Vec2(115, 35));
    igText("Please select an option");

    igSetCursorPos(Vec2(25, 75));
    if (igButton("Login", Vec2(350, 50)))
    {
        update_window_settings(&programStatus, &windowSettings, 2);
    }

    igSetCursorPos(Vec2(25, 130));
    if (igButton("Register", Vec2(350, 50)))
    {
        update_window_settings(&programStatus, &windowSettings, 3);
    }
}

void main_window()
{
    igSetCursorPos(Vec2(igGetWindowWidth() * 0.5f - 175, igGetWindowHeight() * 0.5f - 160));
    igBeginGroup();

    time(&session.live_time);

    igText("  Welcome %s | Session: %s", loginUserProfile.name, ctime(&session.live_time));
    igNewLine();

    if (igButton("View profile", Vec2(350, 50)))
    {
        update_window_settings(&programStatus, &windowSettings, 4);
    }

    if (igButton("View cart", Vec2(350, 50)))
    {
        update_window_settings(&programStatus, &windowSettings, 5);
    }

    if (igButton("Search items", Vec2(350, 50)))
    {
        update_window_settings(&programStatus, &windowSettings, 6);
    }

    if (igButton("Settings", Vec2(350, 50)))
    {
        update_window_settings(&programStatus, &windowSettings, 7);
    }

    if (igButton("Logout", Vec2(350, 50)))
    {
        time(&session.logout_time);
        printf("Session ended at: %s\n", ctime(&session.logout_time));

        session.session_time = session.logout_time - session.login_time;
        session_time_calculator((signed int)session.session_time);

        update_window_settings(&programStatus, &windowSettings, 2);
    }

    igEndGroup();
}

void login_window()
{
    igSetCursorPos(Vec2(68, 50));
    igBeginGroup();

    igText("Username");
    igInputText("##login_username", loginUser.temp_username, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igText("Password");
    igInputText("##login_password", loginUser.temp_password, MAX,
                ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igEndGroup();

    igSetCursorPos(Vec2(25, 230));
    igText("Status: %s", programStatus.output_status != NULL ? programStatus.output_status : "...");

    igSetCursorPos(Vec2(25, 175));
    if (igButton("Login", Vec2(350, 50)))
    {
        if (login_operation(initFile.file, initFile.file_name, loginUser, &loginUserProfile))
        {
            time(&session.login_time);
            update_window_settings(&programStatus, &windowSettings, 1);
        }
        else
        {
            update_output_status(&programStatus, "Failed to login!");
        }
    }

    igSetCursorPos(Vec2(5, 5));
    if (igButton("<", Vec2(25, 25)))
    {
        update_window_settings(&programStatus, &windowSettings, 0);
    }
}

void register_window()
{
    //-----------------LEFT PANEL-----------------//
    igPushItemWidth(-200);
    igSetCursorPos(Vec2(25, 40));
    igBeginGroup();

    igText("Name");
    igInputText("##name", registerUserProfile.name, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igText("Address");
    igInputText("##address", registerUserProfile.address, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igText("Username");
    igInputText("##register_username", registerUserProfile.username, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igText("Password");
    igInputText("##register_password", registerUserProfile.password, MAX, ImGuiInputTextFlags_CharsNoBlank, NULL, NULL);

    igEndGroup();
    igPopItemWidth();


    //-----------------RIGHT PANEL-----------------//
    igPushItemWidth(-20);
    igSetCursorPos(Vec2(200, 40));
    igBeginGroup();

    igText("Age");
    igInputScalar("##age", ImGuiDataType_U8, &registerUserProfile.age, NULL, NULL, NULL,
                  ImGuiInputTextFlags_CharsDecimal);

    igText("Longitude");
    igInputScalar("##longitude", ImGuiDataType_Double, &registerUserProfile.longitude, NULL, NULL, NULL,
                  ImGuiInputTextFlags_CharsDecimal);

    igText("Latitude");
    igInputScalar("##latitude", ImGuiDataType_Double, &registerUserProfile.latitude, NULL, NULL, NULL,
                  ImGuiInputTextFlags_CharsDecimal);

    igText("Max traveling distance");
    igInputScalar("##max_traveling_distance", ImGuiDataType_Double, &registerUserProfile.max_distance, NULL, NULL, NULL,
                  ImGuiInputTextFlags_CharsDecimal);

    igEndGroup();
    igPopItemWidth();

    igSetCursorPos(Vec2(25, 300));
    igText("Status: %s", programStatus.output_status != NULL ? programStatus.output_status : "...");

    igSetCursorPos(Vec2(25, 245));
    if (igButton("Register", Vec2(350, 50)))
    {
        if (registration_operation(initFile.file, initFile.file_name, registerUserProfile))
        {
            update_output_status(&programStatus, "Successfully registered!");
        }
        else
        {
            update_output_status(&programStatus, "Failed to register!");
        }
    }

    igSetCursorPos(Vec2(5, 5));
    if (igButton("<", Vec2(25, 25)))
    {
        update_window_settings(&programStatus, &windowSettings, 0);
    }
}

void view_profile_window()
{

    igSetCursorPos(Vec2(5, 5));
    if (igButton("<", Vec2(25, 25)))
    {
        update_window_settings(&programStatus, &windowSettings, 1);
    }
}

void view_cart_window()
{
    igSetCursorPos(Vec2(5, 5));
    if (igButton("<", Vec2(25, 25)))
    {
        update_window_settings(&programStatus, &windowSettings, 1);
    }
}

void search_window()
{
    igSetCursorPos(Vec2(5, 5));
    if (igButton("<", Vec2(25, 25)))
    {
        update_window_settings(&programStatus, &windowSettings, 1);
    }
}

void settings_window()
{
    igSetCursorPos(Vec2(5, 5));
    if (igButton("<", Vec2(25, 25)))
    {
        update_window_settings(&programStatus, &windowSettings, 1);
    }
}