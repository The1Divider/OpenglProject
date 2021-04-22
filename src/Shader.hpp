#ifndef OPENGLPROJECT_SHADER_HPP
#define OPENGLPROJECT_SHADER_HPP

#define GLM_FORCE_RADIANS

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <initializer_list>
#include <map>
#include <string>


class Shader;
class ShaderProgram;

class Shader {
    public:
        Shader(const std::string& file_name, GLenum type);
        ~Shader();

        GLuint get_handle() const;
        protected:
    private:
        GLuint handle;

        friend class ShaderProgram;
};

class ShaderProgram {
    public:
        ShaderProgram(std::initializer_list<Shader> shader_list);

        void use() const;
        static void unuse();

        GLuint get_handle() const;

        GLint attribute(const std::string& name);

        // clang-format off
        void set_attribute(const std::string& name, GLint size, GLsizei stride, GLuint offset, GLboolean normalize, GLenum type);
        void set_attribute(const std::string& name, GLint size, GLsizei stride, GLuint offset, GLboolean normalize);
        void set_attribute(const std::string& name, GLint size, GLsizei stride, GLuint offset, GLenum type);
        void set_attribute(const std::string& name, GLint size, GLsizei stride, GLuint offset);
        // clang-format off

        GLint uniform(const std::string& name);
        GLint operator[](const std::string& name);

        // clang-format off
        void set_uniform(const std::string& name, float x, float y, float z);
        void set_uniform(const std::string& name, const glm::vec3& v);
        void set_uniform(const std::string& name, const glm::dvec3& v);
        void set_uniform(const std::string& name, const glm::vec4& v);
        void set_uniform(const std::string& name, const glm::dvec4& v);
        void set_uniform(const std::string& name, const glm::dmat4& m);
        void set_uniform(const std::string& name, const glm::mat4& m);
        void set_uniform(const std::string& name, const glm::mat3& m);
        void set_uniform(const std::string& name, float val);
        void set_uniform(const std::string& name, int val);
        // clang-format off

        ~ShaderProgram();

    private:
        ShaderProgram();

        std::map<std::string, GLint> uniforms;
        std::map<std::string, GLint> attributes;

        // opengl id
        GLuint handle;

        void link() const;
};

#endif //OPENGLPROJECT_SHADER_HPP
