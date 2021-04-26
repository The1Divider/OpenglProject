#ifndef OPENGLPROJECT_COLOUR_HPP
#define OPENGLPROJECT_COLOUR_HPP

#include <vector>
#include <map>
#include <unordered_map>
#include "Application.hpp"


class Colour {
   public:
    Colour(float v1, float v2, float v3, float alpha, const char* tag);

    ~Colour() = default;

    void to_hsv();
    void to_rgb();

    void print();

    std::vector<float> value;

   private:
    const char* colour_tag;
};

class ColourProgram {
   public:
    typedef std::vector<Colour*> ColourArray;

    explicit ColourProgram(const Application& application_instance);
    ColourProgram(const Application& application_instance, std::initializer_list<Colour *> colours);
    ColourProgram(const Application& application_instance, std::initializer_list<Colour *> colours, const char* callback);

    ~ColourProgram() = default;

    void cycle_colours(float increment, float interval);

    void add_colour_set(const char* callback, std::initializer_list<Colour *> colour_list);
    ColourArray get_colour_set(const char* callback);

    ColourArray get_current_colour_set();


   private:
    bool can_add = true;
    const Application& app;

    ColourArray current_colour_set;
    std::unordered_map<const char*, ColourArray> colour_map {};

    float current_colour_interval = 0.05;
};

#endif