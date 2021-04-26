#ifndef OPENGLPROJECT_APP_HPP
#define OPENGLPROJECT_APP_HPP


#include <memory>
#include "Application.hpp"
#include "Shader.hpp"
#include "Colour.hpp"

struct VertexType {
    glm::vec3 position;
    glm::vec4 colour;
};


class App : public Application {
public:
    App();

protected:
    virtual void loop();

private:
    float time = 0.f;
    float colour_interval = 1.0;
    float current_colour_interval = colour_interval;

    void set_colours();

    Shader vertex_shader;
    Shader fragment_shader;
    ShaderProgram shader_program;

    // TODO set up perspective
    // glm::mat4 projection = glm::mat4(1.0);
    // glm::mat4 view = glm::mat4(1.0);

    GLuint vao, vbo, ebo;

    std::vector<GLuint> indices;
    std::vector<VertexType> vertices;

};


#endif //OPENGLPROJECT_APP_HPP
