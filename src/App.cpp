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

struct VertexType {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec4 colour;
};

App::App()
        : Application(),
        vertex_shader(SHADER_DIR "vert.shader", GL_VERTEX_SHADER),
        fragment_shader(SHADER_DIR "frag.shader", GL_FRAGMENT_SHADER),
    shader_program({vertex_shader, fragment_shader}) {
    glCheckError(__FILE__,__LINE__);

    std::vector<float> vertices;
    std::vector<GLuint> index;

    Colour* colour1 = new Colour(1.0f, 0.0f, 0.0f, 1.0f, "rgb");
    Colour* colour2 = new Colour(0.0f, 1.0f, 0.0f, 1.0f, "rgb");
    Colour* colour3 = new Colour(0.0f, 0.0f, 1.0f, 1.0f, "rgb");
    Colour* colour4 = new Colour(1.0f, 0.0f, 0.0f, 1.0f, "rgb");


    vertices = {
            0.5f,  0.5f, 0.0f,   colour1->value[0], colour1->value[1], colour1->value[2],  // top right
            0.5f, -0.5f, 0.0f,   colour2->value[0], colour2->value[1], colour2->value[2],  // bottom right
            0.5f, -0.5f, 0.0f,   colour3->value[0], colour3->value[1], colour3->value[2],  // bottom left
           -0.0f, -0.5f, 0.0f,   colour4->value[0], colour4->value[1], colour4->value[2]   // top left
            //        pos                colour
    };

    index = {
            0, 1, 3,
            1, 2, 3
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType),
    vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size(), index.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void App::loop() {
    // exit on window close button pressed
    if (glfwWindowShouldClose(get_window()))
        exit();

    //float t = get_time();
    // set matrix : projection + view
    // projection = glm::perspective(float(2.0 * atan(getHeight() / 1920.f)),
    //                              get_window_ratio(), 0.1f, 100.f);
    // view = glm::lookAt(glm::vec3(20.0 * sin(t), 20.0 * cos(t), 20.0),
    //                   glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));

    // clear
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    shader_program.use();

    // send uniforms
    // shader_program.set_uniform("projection", projection);
    // shader_program.set_uniform("view", view);

    glCheckError(__FILE__, __LINE__);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glCheckError(__FILE__, __LINE__);
    glDrawElements(GL_TRIANGLES,         // mode
                   6,  // count
                   GL_UNSIGNED_INT,      // type
                   NULL                  // element array buffer offset
    );

    glBindVertexArray(0);

    shader_program.unuse();
}
