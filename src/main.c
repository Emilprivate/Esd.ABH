#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../Libraries/sokol/sokol_app.h"
#include "../Libraries/sokol/sokol_gfx.h"
#include "../Libraries/sokol/sokol_glue.h"
#include "../Libraries/sokol/sokol_imgui.h"
#include "cimgui.h"

#include "Header/utilities.h"
#include "UI/Header/user_interface.h"
#include "Definitions/struct_definitions.h"
#include "Header/profile_management.h"

#define WIDTH  750
#define HEIGHT 600

static void init(void);
static void frame(void);
static void cleanup(void);
static void event(const sapp_event* ev);
static void init_font();

void debug_admin_profile(FILE * file, char * file_name);
void initialise_database(FILE * file, char * file_name);

static struct{
    sg_pass_action pass_action;
} state;

sapp_desc sokol_main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    srand(time(NULL));

    FILE * file = NULL;
    char * file_name = "Userprofiles.txt";

    initialise_database(file, file_name);

    debug_admin_profile(file, file_name);

    return (sapp_desc)
    {
            .init_cb = init,
            .frame_cb = frame,
            .cleanup_cb = cleanup,
            .event_cb = event,
            .window_title = "Welcome to P1-extension | By Emil S. Doganci",
            .width = WIDTH,
            .height = HEIGHT,
            .icon.sokol_default = true,
    };
}

static void init(void)
{
    sg_setup(&(sg_desc){ .context = sapp_sgcontext() });
    simgui_setup(&(simgui_desc_t){ 0 });

    state.pass_action = (sg_pass_action) {
        .colors[0] = { .action = SG_ACTION_CLEAR, .value = { 0.6f, 0.6f, 0.6f, 1.0f } }
    };
}

static void frame(void) {

    simgui_new_frame(&(simgui_frame_desc_t){
        .width = sapp_width(),
        .height = sapp_height(),
        .delta_time = sapp_frame_duration(),
        .dpi_scale = sapp_dpi_scale(),
    });

    initialise_ui(WIDTH, HEIGHT);

    sg_begin_default_pass(&state.pass_action, sapp_width(), sapp_height());

    simgui_render();

    sg_end_pass();
    sg_commit();
}

static void cleanup(void)
{
    simgui_shutdown();
    sg_shutdown();
}

static void event(const sapp_event* ev)
{
    simgui_handle_event(ev);
}

void debug_admin_profile(FILE * file, char * file_name)
{
    t_user_profile * database = load_database(file, file_name);
    t_user_profile admin_profile = {count_lines_in_file(file, file_name), "Admin", "Vesterbro_69", "admin", "admin", 69, 69, 10000, 420, Bus};

    upload_profile(file, file_name, admin_profile, database);
}

void initialise_database(FILE * file, char * file_name)
{
    file = fopen(file_name, "a");
    validate_file_pointer(file);
    fclose(file);
}

void init_font()
{
    ImGuiIO * io = igGetIO();
    ImFontAtlas_Clear(io->Fonts);
    ImFontAtlas_AddFontFromFileTTF(io->Fonts,"Verdana.ttf",14, NULL, ImFontAtlas_GetGlyphRangesDefault(io->Fonts));
    ImFontAtlas_Build(io->Fonts);
}