#ifndef OPENGLPROJECT_COLOUR_HPP
#define OPENGLPROJECT_COLOUR_HPP

#include <vector>

class Colour {
public:
    Colour(float v1, float v2, float v3, float alpha, std::string tag);
    ~Colour();

    void to_hsv();
    void to_rgb();
    void print();

    std::vector<float> value;

private:
    std::string colour_tag;
};

#endif