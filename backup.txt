#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "user_interface.h"
#include "Libraries/cimgui/cimgui.h"

t_i_cs init;
t_d_uii debug_ui;
t_m_uii main_ui;
t_s_uii session_ui;

ImVec2 Vec2(float x, float y)
{
    return (ImVec2){x, y};
}

ImVec4 Vec4(float a, float b, float c, float d)
{
    return (ImVec4){a, b, c, d};
}

void load_styles()
{
    ImVec4* colors = igGetStyle()->Colors;
    {
        colors[ImGuiCol_WindowBg] = Vec4(0.06f, 0.06f, 0.06f, 1.00f);

        colors[ImGuiCol_FrameBg] = Vec4(0.11f, 0.11f, 0.11f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = Vec4(0.11f, 0.11f, 0.11f, 1.00f);

        colors[ImGuiCol_Button] = Vec4(1.00f, 0.00f, 0.2f, 1.00f);
        colors[ImGuiCol_ButtonActive] = Vec4(1.00f, 0.0f, 0.0f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = Vec4(1.00f, 0.0f, 0.0f, 0.00f);

        colors[ImGuiCol_TextDisabled] = Vec4(0.37f, 0.37f, 0.37f, 1.00f);
    }

    ImGuiStyle* style = igGetStyle();
    {
        style->WindowPadding = Vec2(0.4f, 0.4f);
        style->WindowBorderSize = 0.5f;

        style->FramePadding = Vec2(0.8f, 0.6f);
        style->FrameRounding = 3.f;
        style->FrameBorderSize = 1.f;
    }
}

void initialise_ui(int WIDTH, int HEIGHT)
{
    ImVec2 CENTER = Vec2(WIDTH * 0.5f, HEIGHT * 0.5f);

    if (!init.initialised)
    {
        igStyleColorsDark(NULL);
        load_styles();

        init.initialised = true;
    }

    igSetNextWindowPos(CENTER, ImGuiCond_Always, Vec2(0.5f,0.5f));
    igSetNextWindowSize(Vec2(WIDTH, HEIGHT), ImGuiCond_Once);

    igBegin(" ", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    igPushStyleVar_Float(ImGuiStyleVar_ChildRounding, 3.f);
    {

        ImVec2 main_cf = Vec2(400, 250);

        igSetNextWindowPos(CENTER, ImGuiCond_Always, Vec2(0.5f,0.5f));
        igBeginChildFrame("#main", main_cf, ImGuiWindowFlags_ChildWindow);
        {

            igSetCursorPos(Vec2(115, 35));
            igText("Please select an option");

            igSetCursorPos(Vec2(25, 75));
            if(igButton("Login", Vec2(350, 50)))
                main_ui.render_login = true;

            igSetCursorPos(Vec2(25, 130));
            if(igButton("Register", Vec2(350, 50)))
                main_ui.render_registration = true;




            /*
                         igSetCursorPos(Vec2(0, 143));
            if(igButton("Turn on Demo Window", Vec2(400, 50)))
                debug_ui.render_demo_window = !debug_ui.render_demo_window;

            if(igButton("Turn on Debug Window", Vec2(400, 50)))
                debug_ui.render_debuglog_window = !debug_ui.render_debuglog_window;*/

            if (debug_ui.render_debuglog_window)
                igShowDebugLogWindow(NULL);
            else if (debug_ui.render_demo_window)
                igShowDemoWindow(NULL);

        }igEndChildFrame();

    }igPopStyleVar(1);
    igEnd();
}



