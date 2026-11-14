#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include "vec3.h"

inline int convert_to_channel(double percent_color) {
    auto clamped_color = std::clamp(percent_color, 0.0, 1.0);
    double byte_color = clamped_color * 256.0;
    int byte_color_clamped = byte_color > 255 ? 255 : int(byte_color);
    return byte_color_clamped;
}

inline void write_color(std::ostream& out, const Color& pixel_color) {
    auto r = convert_to_channel(pixel_color.x());
    auto g = convert_to_channel(pixel_color.y());
    auto b = convert_to_channel(pixel_color.z());

    out << r << ' ' << g << ' ' << b << '\n';
}

#endif