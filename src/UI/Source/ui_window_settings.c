#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "cimgui.h"

#include "../../Definitions/struct_definitions.h"

#include "../Header/ui_window_settings.h"
#include "../../Header/utilities.h"


void initialise_initial_window_settings(t_new_window *windowSettings) {
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

void initialise_main_window_settings(t_new_window *windowSettings) {
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(425, 375);

    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}

void initialise_registration_window_settings(t_new_window *windowSettings) {
    ImVec2 CENTER_POS = Vec2(windowSettings->WIDTH * 0.5f, windowSettings->HEIGHT * 0.5f);
    ImVec2 MAIN_CHILD_FRAME = Vec2(400, 320);

    windowSettings->pos = CENTER_POS;
    windowSettings->pos_cond = ImGuiCond_Always;
    windowSettings->child_size = MAIN_CHILD_FRAME;
    windowSettings->windowflags = windowSettings->windowflags;
}