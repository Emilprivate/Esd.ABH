#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "cimgui.h"

#include "../Definitions/struct_definitions.h"

#include "ui_window_settings.h"
#include "../Utilities/utilities.h"

void default_window_settings(t_new_window *windowSettings)
{
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(windowSettings->WIDTH, windowSettings->HEIGHT);

    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}

void initialise_initial_window_settings(t_new_window *windowSettings)
{
    ImVec2 MAIN_FRAME = Vec2(windowSettings->WIDTH, windowSettings->HEIGHT);
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(400, 250);

    windowSettings->size = MAIN_FRAME;
    windowSettings->size_cond = ImGuiCond_Once;
    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}

void initialise_login_window_settings(t_new_window *windowSettings)
{
    ImVec2 MAIN_FRAME = Vec2(windowSettings->WIDTH, windowSettings->HEIGHT);
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(400, 250);

    windowSettings->size = MAIN_FRAME;
    windowSettings->size_cond = ImGuiCond_Once;
    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}

void initialise_registration_window_settings(t_new_window *windowSettings)
{
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(windowSettings->WIDTH * 0.53f, windowSettings->HEIGHT * 0.53f);

    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}

void initialise_main_window_settings(t_new_window *windowSettings)
{
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(windowSettings->WIDTH * 0.9f, windowSettings->HEIGHT * 0.9f);

    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}

void initialise_view_profile_window_settings(t_new_window *windowSettings)
{
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(windowSettings->WIDTH * 0.53f, windowSettings->HEIGHT * 0.53f);

    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}

void initialise_view_cart_window_settings(t_new_window *windowSettings)
{
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(windowSettings->WIDTH * 0.9f, windowSettings->HEIGHT * 0.9f);

    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}

void initialise_search_window_settings(t_new_window *windowSettings)
{
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(windowSettings->WIDTH * 0.9f, windowSettings->HEIGHT * 0.9f);

    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}

void initialise_settings_window_settings(t_new_window *windowSettings)
{
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(windowSettings->WIDTH * 0.9f, windowSettings->HEIGHT * 0.9f);

    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}