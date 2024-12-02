#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void writeColor(std::ostream& out, const color& pixelColor){
    // Write a color to std::out

    // get pixel colors from given pixel.
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    // Translate 0-1 values to 0-255
    int rbyte = int(255.999 *r);
    int gbyte = int(255.999 *g);
    int bbyte = int(255.999 *b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif