#ifndef VAR
#define VAR

#include <iostream>
#include <disk.hpp>

using namespace std;

#define M_PI 3.14159265358979323846

Uint8 attempt_count = 3;

bool win = false;
bool quit = false;

bool left_keyup = false;
bool right_keyup = false;

double left_deg = 15;
double right_deg = -15;

string path = disk_path()+"\\";
string name = "pinball";

double ball_velocity_y = 1;
double ball_velocity_x = 0;
const double gravity = 0.25;
const double max_velocity_x = 5.0;
const double max_velocity_y = 10.0;

#endif