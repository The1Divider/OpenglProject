#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>

#include <iostream>
#include <vector>

#include "App.hpp"
#include "glError.hpp"
#include "Colour.hpp"

#define SHADER_DIR "../shaders/"



void App::set_colours() {
    // set colours used (for organization, this can be done in the object creation method)
    auto* colour1 = new Colour(0.0f,   1.0f, 1.0f, 1.0f, "hsv");
    auto* colour2 = new Colour(90.0f,  1.0f, 1.0f, 1.0f, "hsv");
    auto* colour3 = new Colour(180.0f, 1.0f, 1.0f, 1.0f, "hsv");
    auto* colour4 = new Colour(270.0f, 1.0f, 1.0f, 1.0f, "hsv");
    Application::set_colour_program_instance({colour1, colour2, colour3, colour4}, "square");
}

App::App()
        : Application(),
        vertex_shader(SHADER_DIR "vert.shader", GL_VERTEX_SHADER),
        fragment_shader(SHADER_DIR "frag.shader", GL_FRAGMENT_SHADER),
        shader_program({vertex_shader, fragment_shader}) {
    glCheckError(__FILE__,__LINE__);

    // Set vertex colour
    set_colours();

    for (auto& c : colour_program->get_current_colour_set()) {
        c->to_rgb();
    }

    // Set vertex pos
    float vertex_array[12] = {
             0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
    };

    // Build vertex objects
    for (int index = 0; index < sizeof(vertex_array) / sizeof(float); index += 3) {
        VertexType temp{};
        ColourProgram::ColourArray colour_array = colour_program->get_current_colour_set();
        Colour* colour = colour_array[index/3];
        temp.position = glm::vec3(vertex_array[index], vertex_array[index + 1], vertex_array[index + 2]);
        temp.colour = glm::vec4(colour->value[0], colour->value[1], colour->value[2], colour->value[3]);
        vertices.push_back(temp);
    }

    // Set indices
    indices = {
            0, 1, 3,
            1, 2, 3
    };

    // gen buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // Bind vao
    glBindVertexArray(vao);

    // Bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType), vertices.data(), GL_STATIC_DRAW);

    glCheckError(__FILE__, __LINE__);

    // Set vertex attrs
    shader_program.set_attribute("position", 3, sizeof(VertexType), offsetof(VertexType, position));
    shader_program.set_attribute("colour", 4, sizeof(VertexType), offsetof(VertexType, colour));

    // Bind ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glCheckError(__FILE__, __LINE__);
}

void App::loop() {
    // exit on window close button pressed

    ColourProgram::ColourArray current_colour_set = colour_program->get_current_colour_set();
    if (glfwWindowShouldClose(get_window())) {
        // Free colour objects (also not needed? should colours be stack objs?)
        for (Colour *c : current_colour_set) {
            delete c;
        }
        exit();
    }

    // calculate if colours need to be updated
    colour_interval = .005;
    current_colour_interval -= get_frame_time_delta();

    if (current_colour_interval <= 0) {
        colour_program->cycle_colours(1, colour_interval);
        current_colour_interval = colour_interval;
    }

    // Update vertex colour attr
    for (int index = 0; index < vertices.size(); index++) {
        Colour* colour = current_colour_set[index];
        vertices[index].colour = glm::vec4(colour->value[0], colour->value[1], colour->value[2], colour->value[3]);
    }

    // Update vbo data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType), vertices.data(), GL_STATIC_DRAW);

    glCheckError(__FILE__, __LINE__);

    // Set clear colour values (can be done in setup?)
    float h = 270, s = 0.6f, v = 0.7f;
    Colour clear_colour(h, s, v, 1.0f, "hsv");
    clear_colour.to_rgb();

    // Set clear colour
    glClearColor(clear_colour.value[0], clear_colour.value[1], clear_colour.value[2], 0.0);

    // Clear colour and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glCheckError(__FILE__, __LINE__);

    shader_program.use();

    glCheckError(__FILE__, __LINE__);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES,         // mode
                   6,                    // count
                   GL_UNSIGNED_INT,      // type
                   nullptr                  // element array buffer offset
    );
    //shader_program.unuse();
}
