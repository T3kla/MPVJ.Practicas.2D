#pragma once

constexpr double PI = 355. / 113.;

double ToDeg(const double &rad) { return (rad * 180) / PI; }
double ToRad(const double &deg) { return (deg * PI) / 180; }
