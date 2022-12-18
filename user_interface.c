#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "Libraries/cimgui/cimgui.h"

#include "user_interface.h"
#include "utilities.h"

t_init_window    init_window;
t_active_window  active_window;
t_program_status program_status;
t_new_window     new_window_settings;

// TODO: Fix the "go back" button

// window prototypes
void login_window();
void register_window();

typedef struct function_table_struct
{
    const char* name;
    void (*func)(void);
} t_function_table;

t_function_table function_table[] =
        {
                {"login_window", login_window},
                {"register_window", register_window}
        };

// function prototypes
void run_new_window(t_new_window newWindowInfo, void callActiveWindow());
void update_program_settings(t_active_window * window, t_program_status * program, int id, bool window_status, bool settings_status);
void update_window_status(t_active_window * activeWindow, int currentActiveWidowId);
void * current_active_window(t_function_table functionTable[], int currentActiveWindowId);
int find_active_window_id(t_active_window activeWindow);

void initialise_ui(float WIDTH, float HEIGHT) {
    ImVec2 MAIN_FRAME = Vec2(WIDTH, HEIGHT);
    ImVec2 CENTER_POS = Vec2(WIDTH * 0.5f, HEIGHT * 0.5f);

    if (!init_window.initialised) {
        igStyleColorsDark(NULL);
        load_styles();

        init_window.initialised = !init_window.initialised;
    }

    // Create the main window
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
    window_flags |= ImGuiWindowFlags_NoSavedSettings;
    window_flags |= ImGuiWindowFlags_NoInputs;

    igSetNextWindowPos(CENTER_POS, ImGuiCond_Always, Vec2(0.5f, 0.5f));
    igSetNextWindowSize(MAIN_FRAME, ImGuiCond_Once);

    igBegin("initial_ui", 0, window_flags);
    igPushStyleVar_Float(ImGuiStyleVar_ChildRounding, 100.f);
    {

        ImVec2 MAIN_CHILD_FRAME = Vec2(400, 250);

        if (!new_window_settings.init){
            new_window_settings.size = MAIN_FRAME;
            new_window_settings.size_cond = ImGuiCond_Once;
            new_window_settings.pos = CENTER_POS;
            new_window_settings.pos_cond = ImGuiCond_Always;
            new_window_settings.child_size = MAIN_CHILD_FRAME;
            new_window_settings.windowflags = window_flags;
            new_window_settings.init = !new_window_settings.init;
        }

        igSetNextWindowPos(CENTER_POS, ImGuiCond_Always, Vec2(0.5f, 0.5f));
        igBeginChildFrame(1, MAIN_CHILD_FRAME, ImGuiWindowFlags_ChildWindow);
        {

            igSetCursorPos(Vec2(115, 35));
            igText("Please select an option");

            igSetCursorPos(Vec2(25, 75));
            if (igButton("Login", Vec2(350, 50)))
            {
                active_window.render_login = true;
                update_program_settings(&active_window, &program_status, find_active_window_id(active_window), true, true);
            }

            igSetCursorPos(Vec2(25, 130));
            if (igButton("Register", Vec2(350, 50)))
            {
                active_window.render_registration = true;
                update_program_settings(&active_window, &program_status, find_active_window_id(active_window), true, true);
            }
        }
        igEndChildFrame();
    }
    igPopStyleVar(1);
    igEnd();


    if (program_status.current_active_window_status && program_status.current_window_settings_status)
    {
        run_new_window(new_window_settings, current_active_window(function_table, program_status.current_active_window_id));
    }
}

void login_window()
{
    igSetCursorPos(Vec2(25, 150));
    if (igButton("Login", Vec2(350, 50)))
    {
        printf("Logged in!\n");
    }

    igSetCursorPos(Vec2(150, 220));
    if (igButton("<-", Vec2(100, 25)))
    {
        update_program_settings(&active_window, &program_status, find_active_window_id(active_window), false, false);
    }
}

void register_window()
{
    igSetCursorPos(Vec2(25, 150));
    if (igButton("Register", Vec2(350, 50)))
    {
        printf("Registered!\n");
    }

    igSetCursorPos(Vec2(150, 220));
    if (igButton("<-", Vec2(100, 25)))
    {
        update_program_settings(&active_window, &program_status, find_active_window_id(active_window), false, false);
    }
}

void run_new_window(t_new_window newWindowInfo, void callActiveWindow())
{
    igSetNextWindowPos(newWindowInfo.pos, newWindowInfo.pos_cond, Vec2(0.5f,0.5f));
    igSetNextWindowSize(newWindowInfo.size, newWindowInfo.size_cond);

    igBegin(function_table[program_status.current_active_window_id].name, 0, newWindowInfo.windowflags);
    igPushStyleVar_Float(ImGuiStyleVar_ChildRounding, 100.f);
    {

        igSetNextWindowPos(newWindowInfo.pos, newWindowInfo.pos_cond, Vec2(0.5f,0.5f));
        igBeginChildFrame(1, newWindowInfo.child_size, ImGuiWindowFlags_ChildWindow);
        {
            callActiveWindow();
        }igEndChildFrame();


    }igPopStyleVar(1);
    igEnd();
}

void * current_active_window(t_function_table functionTable[], int currentActiveWindowId)
{
    return functionTable[currentActiveWindowId].func;
}

void update_window_status(t_active_window * activeWindow, int currentActiveWidowId)
{
    printf("Updating window statuses...\n");
    for (int j = 0; j < sizeof(activeWindow) / sizeof(bool); j++)
    {
        if (currentActiveWidowId != j)
        {
            ((bool*)&activeWindow)[j] = false;
        }
    }
    printf("Updated window status!\n");
}

void update_program_settings(t_active_window * window, t_program_status * program, int id, bool window_status, bool settings_status){
    printf("Updating program settings...\n");
    program->current_active_window_id = id;
    program->current_active_window_status = window_status;
    program->current_window_settings_status = settings_status;
    update_window_status(window, id);
    printf("Updated program settings!\n");
}

int find_active_window_id(t_active_window activeWindow)
{
    printf("Finding active window id...\n");
    // Loop through each member of the struct
    for (int i = 0; i < sizeof(activeWindow) / sizeof(bool); i++) {
        // Check if the current member is true
        if (((bool*)&activeWindow)[i]) {
            printf("Found current active window id: %d\n", i);
            printf("Setting current active window id to %d!\n", i);
            return i;
        }
    }

    return -1;
}