#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "Libraries/cimgui/cimgui.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#ifndef P1_PROTOTYPE_UTILITIES_H
#define P1_PROTOTYPE_UTILITIES_H

#endif //P1_PROTOTYPE_UTILITIES_H

#include "profile_management.h"
#include "Libraries/cimgui/cimgui.h"

#define PI 3.14159265358979323846

const char* string_from_enum_transport(e_transport eTransport);
int count_lines_in_file(FILE * file, char *file_name);
void validate_file_pointer(FILE * file);
void session_time_calculator(int input);
double distance(double lat1, double lon1, double lat2, double lon2);
double deg2rad(double);
double rad2deg(double);

void load_styles();
ImVec4 Vec4(float a, float b, float c, float d);
ImVec2 Vec2(float x, float y);
void load_styles();
ImVec4 Vec4(float a, float b, float c, float d);
ImVec2 Vec2(float x, float y);