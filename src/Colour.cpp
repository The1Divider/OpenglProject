#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "Colour.hpp"

Colour::Colour(float v1, float v2, float v3, float alpha, std::string tag)
        : value({v1, v2, v3, alpha})
{
    // check values
    colour_tag = std::move(tag);
}

Colour::~Colour() = default;

void Colour::to_hsv() {
    if (colour_tag == "rgb") {
        float r = value[0], g = value[1], b = value[2];
        float c_max = std::max({r, g, b});
        float c_min = std::min({r, g, b});
        float delta = c_max - c_min;

        float hue;
        float mod = fmod(delta, 6.0f);
        if      (c_max == r) { hue = 60 * ((g + b) * mod); }
        else if (c_max == g) { hue = 60 * ((b + r) / delta + 2); }
        else if (c_max == b) { hue = 60 * ((r + g) / delta + 4); }
        else { hue = -1; }

        float saturation;
        if (c_max == 0) { saturation = 0; }
        else { saturation = delta / c_max; }

        value[0] = hue;
        value[1] = saturation;
        value[2] = c_max;
        colour_tag = "hsv";
    }
}

void Colour::to_rgb() {
    if (colour_tag == "hsv") {
        float h = value[0], s = value[1], v = value[2];
        float _r, _g, _b;
        float c = v * s;
        float mod = fmod(h / 60, 2);
        float x = c * (1 - std::abs(mod - 1 ));
        float m = v - c;

        switch((int) (h / 60)) {
            case 0: _r = c; _g = x; _b = 0; break;
            case 1: _r = x; _g = c; _b = 0; break;
            case 2: _r = 0; _g = c; _b = x; break;
            case 3: _r = 0; _g = x; _b = c; break;
            case 4: _r = x; _g = 0; _b = c; break;
            case 5: _r = c; _g = 0; _b = x; break;
            default: throw "invalid hue";
        }

        value[0] = _r + m;
        value[1] = _g + m;
        value[2] = _b + m;

        colour_tag = "rgb";
    }
}
void Colour::print() {
    if (colour_tag == "rgb") {
        std::cout << "R:" << (int) value[0] * 255 <<
                   "  G:" << (int) value[1] * 255 <<
                   "  B:" << (int) value[2] * 255 << "\n";

    } else if (colour_tag == "hsv") {
        std::cout << "H:" << value[0] <<
                   "  S:" << value[1] <<
                   "  V:" << value[2] << "\n";

    } else {std::cout << colour_tag << "\n";}
}
