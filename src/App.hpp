#ifndef OPENGLPROJECT_APP_HPP
#define OPENGLPROJECT_APP_HPP


#include "Application.hpp"
#include "Shader.hpp"

class App : public Application {
public:
    App();

protected:
    virtual void loop();

private:

    float time = 0.f;

    Shader vertex_shader;
    Shader fragment_shader;
    ShaderProgram shader_program;

    glm::mat4 projection = glm::mat4(1.0);
    glm::mat4 view = glm::mat4(1.0);

    GLuint vao, vbo, ibo;
};


#endif //OPENGLPROJECT_APP_HPP
