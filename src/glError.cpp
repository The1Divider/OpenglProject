#include <glad/glad.h>
#include <string>
#include <iostream>

#include "glError.hpp"

void glCheckError(const char* file, unsigned int line) {
    GLenum error_code = glGetError();

    while (error_code != GL_NO_ERROR) {
        std::string file_string(file);
        std::string error = " * Unknown error * ";

        switch (error_code) {
            case GL_INVALID_ENUM:      error = "GL_INVALID_ENUM";      break;
            case GL_INVALID_VALUE:     error = "GL_INVALID_VALUE";     break;
            case GL_INVALID_OPERATION: error = "GL_INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:    error = "GL_STACK_OVERFLOW";    break;
            case GL_STACK_UNDERFLOW:   error = "GL_STACK_UNDERFLOW";   break;
            case GL_OUT_OF_MEMORY:     error = "GL_OUT_OF_MEMORY";     break;
            default: break;
        }

        std::cerr << "[OPENGLERROR] file =" << file
                  << "\n line = " << line
                  << "\n error: " << error
                  << "\n";

        error_code = glGetError();
    }
};
