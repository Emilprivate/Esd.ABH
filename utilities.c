#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "Libraries/cimgui/cimgui.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



#include "utilities.h"

#define SECONDS_PER_WEEK   (7 * 24 * (60 * 60))
#define SECONDS_PER_DAY    (24 * (60 * 60))
#define SECONDS_PER_HOUR   (60 * 60)
#define SECONDS_PER_MINUTE (60)

const char* string_from_enum_transport(e_transport eTransport)
{
    const char *strings[] = {"Walk", "Bicycle", "Car", "Bus"};
    return strings[eTransport];
}

void validate_file_pointer(FILE * file)
{
    if (file == NULL)
    {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
}

int count_lines_in_file(FILE * file, char *file_name)
{
    int count_lines = 0;

    file = fopen(file_name, "r");
    validate_file_pointer(file);

    char chr = getc(file);
    while (chr != EOF)
    {
        if (chr == '\n')
        {
            count_lines = count_lines + 1;
        }
        chr = getc(file);
    }
    fclose(file);

    return count_lines;
}

void session_time_calculator(int input){
    int min, hour;

    input    = input % SECONDS_PER_WEEK;
    input    = input % SECONDS_PER_DAY;

    hour     = input / SECONDS_PER_HOUR;
    input    = input % SECONDS_PER_HOUR;

    min      = input / SECONDS_PER_MINUTE;
    input    = input % SECONDS_PER_MINUTE;

    printf("Session was active for %d hours, %d minutes, %d seconds\n\n", hour, min, input);
}

double distance(double lat1, double lon1, double lat2, double lon2) {
    double theta, dist;
    if ((lat1 == lat2) && (lon1 == lon2)) {
        return 0;
    }
    else {
        theta = lon1 - lon2;
        dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
        dist = acos(dist);
        dist = rad2deg(dist);
        dist = dist * 60 * 1.1515;
        dist = dist * 1.609344;
    }
    return dist;
}

double deg2rad(double deg) {
    return (deg * PI / 180);
}

double rad2deg(double rad) {
    return (rad * 180 / PI);
}

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

        style->FramePadding = Vec2(5.5f, 5.5f);
        style->FrameRounding = 3.f;
        style->FrameBorderSize = 1.f;
    }
}