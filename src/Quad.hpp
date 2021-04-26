/* **************************************** *\
Name:         Quad.hpp.h

Contributors: 
            ~ numpee

Licence:      MIT
\* **************************************** */
#ifndef OPENGLPROJECT_QUAD_HPP
#define OPENGLPROJECT_QUAD_HPP


#include <vector>
#include "Shader.hpp"

struct VertexType {
    glm::vec3 position;
    glm::vec4 colour;
};

class Quad {
   public:
    Quad();
    ~Quad() = default;

    void set_colour_array();

   private:
    Shader vertex_shader;
    Shader fragment_shader;
    ShaderProgram shader_program;

    GLuint vao, vbo, ebo;

    std::vector<GLuint> indices;
    std::vector<VertexType> vertices;


};


#endif //OPENGLPROJECT_QUAD_HPP
