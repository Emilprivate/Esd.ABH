#ifndef P1_PROTOTYPE_UTILITIES_H
#define P1_PROTOTYPE_UTILITIES_H

#include "../Definitions/enum_definitions.h"
#include "../Definitions/struct_definitions.h"

void update_output_status(t_program_status * program, char * status);
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

#endif //P1_PROTOTYPE_UTILITIES_H