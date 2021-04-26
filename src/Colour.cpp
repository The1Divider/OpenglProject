#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "Colour.hpp"
#include "Application.hpp"

Colour::Colour(float v1, float v2, float v3, float alpha, const char* tag)
        : value({v1, v2, v3, alpha}), colour_tag(tag)
{
    // check values
}

void Colour::to_hsv() {
    if (colour_tag == "rgb") {
        float r = value[0], g = value[1], b = value[2];
        float min, max, delta;
        float _h, _s, _v;

        min = r < g ? r : g;
        min = min < b ? min : b;

        max = r > g ? r : g;
        max = max > b ? max : b;

        _v = max;
        delta = max - min;
        if (delta < 0.00001f) {
            _s = 0.0f;
            _h = 0.0f;
        }
        if (max > 0.0f) {
            _s = delta / max;
        } else {
            throw std::runtime_error("Division by zero in rgb conversion");
        }
        if (r == max) {
            _h = (g - b) / delta;
        } else if (g == max) {
            _h = 2.0f + (b - r) / delta;
        } else {
            _h = 4.0f + (r - g) / delta;
        }
        _h *= 60.0f;

        if (_h < 0.0f) {
            _h += 360;
        }
        value[0] = _h;
        value[1] = _s;
        value[2] = _v;
        colour_tag = "hsv";
    }
}

void Colour::to_rgb() {
    if (colour_tag == "hsv") {
        float h = value[0], s = value[1], v = value[2];
        float _r, _g, _b;
        float hh, p, q, t, ff;
        int i;

        if (s == 0.0) {
            _r = 0.0f;
            _g = 0.0f;
            _b = 0.0f;
        } else {
            hh = h;
            if (hh >= 360.0f) hh = 0.0f;
            hh /= 60.0f;
            i = (int)hh;
            ff = hh - i;
            p = v * (1.0f - s);
            q = v * (1.0f - (s * ff));
            t = v * (1.0f - (s * (1.0f - ff)));

            switch(i) {
                case 0: _r = v; _g = t; _b = p; break;
                case 1: _r = q; _g = v; _b = p; break;
                case 2: _r = p; _g = v; _b = t; break;
                case 3: _r = p; _g = q; _b = v; break;
                case 4: _r = t; _g = p; _b = v; break;
                case 5: default: _r = v; _g = p; _b = q; break;
            }

        }
        value[0] = _r;
        value[1] = _g;
        value[2] = _b;

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

ColourProgram::ColourProgram(const Application& application_instance)
        : app(application_instance) {}

ColourProgram::ColourProgram(const Application& application_instance, std::initializer_list<Colour*> colours)
        : can_add(false), app(application_instance), current_colour_set(colours) {}

ColourProgram::ColourProgram(const Application& application_instance, std::initializer_list<Colour*> colours, const char* callback)
        : app(application_instance) {
    add_colour_set(callback, colours);
}


void ColourProgram::add_colour_set(const char* callback, std::initializer_list<Colour*> colour_list) {
    if (can_add) {
        colour_map[callback] = colour_list;
    } else {
        throw std::runtime_error("[ERROR] Can not add to a Colour Program initialized without a callback");
    }
}

ColourProgram::ColourArray ColourProgram::get_colour_set(const char* callback) {
    try {
        return colour_map.at(callback);
    } catch (const std::out_of_range& oor) {
        throw std::runtime_error("[ERROR] Invalid callback");
    }
}

ColourProgram::ColourArray ColourProgram::get_current_colour_set() {
    if (!current_colour_set.empty()) {
        return current_colour_set;
    } else {
        throw std::runtime_error("[ERROR] No current colour set");
    }
}

void ColourProgram::cycle_colours(float increment, float interval) {
    // calculate if colours need to be updated
    current_colour_interval -= app.get_frame_time_delta();

    if (current_colour_interval <= 0) {
        // Circles through hsv values (takes and returns normalized rgb)
        for (auto& c : current_colour_set) {
            c->to_hsv();
            float h_value = c->value[0];
            if (h_value + increment <= 360.0f) {
                c->value[0] += increment;
            } else {
                c->value[0] = h_value + increment - 360.0f;
            }
            c->to_rgb();
        }
        current_colour_interval = interval;
    }
}
