#ifndef VAR
#define VAR

#include <iostream>

using namespace std;

#define M_PI 3.14159265358979323846

bool left_keyup = false;
bool right_keyup = false;

string path = "Z:/cpp/pinball/image/";
string name = "pinball";

double ball_velocity_y = 1;
double ball_velocity_x = 0;
const double gravity = 0.25;
const double max_velocity_x = 5.0;
const double max_velocity_y = 10.0;

#endif