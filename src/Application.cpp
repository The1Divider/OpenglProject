#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include "Application.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Application* current_application = NULL;

Application& Application::get_instance() {
    if (current_application) {
        return *current_application;
    } else {
        throw std::runtime_error("No current application");
    }
}

Application::Application()
        : state(stateReady), width(800), height(600), title("Stupid Head") {

    current_application = this;

    std::cout << "[INFO] GLFW Initialisation" << "\n";

    // initialize the GLFW library
    if (!glfwInit()) {
        throw std::runtime_error("Failed to init GLFW");
    }


    // Setting OpenGl version
    int major = 4;
    int minor = 6;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to init window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to init GLAD");
    }

    // Display context
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "[INFO] Renderer: " << renderer << "\n";
    std::cout << "[INFO] OpenGL version supported:  " << version << "\n";

    glEnable(GL_DEPTH_TEST); // enable depth testing
    glDepthFunc(GL_LESS); // smaller values get rendered as 'closer' object
}

Application::~Application() = default;

GLFWwindow* Application::get_window() const {
    return window;
}

void Application::exit() {
    state = stateExit;
}

float Application::get_frame_time_delta() const {
    return deltaTime;
}

float Application::get_time() const {
    return time;
}

void Application::run() {
    state = stateRun;

    glfwMakeContextCurrent(window);

    time = glfwGetTime();

    while(state == stateRun) {
        // get new (delta)time
        float t = glfwGetTime();
        deltaTime = t - time;
        time = t;

        // detect if window dimensions have changed
        detect_window_dimension_change();

        // execute the frame code;
        loop();

        // Swap buffers
        glfwSwapBuffers(window);

        // Pool events and process
        glfwPollEvents();
    }
    glfwTerminate();
}

void Application::detect_window_dimension_change() {
    int w, h;

    glfwGetWindowSize(get_window(), &w, &h);

    dimension_changed = (w != width or h != height);
    if (dimension_changed) {
        width = w;
        height = h;
        glViewport(0, 0, width, height);
    }
}

int Application::get_width() const {
    return width;
}

int Application::get_height() const {
    return height;
}

float Application::get_window_ratio() const{
    return (float) width / (float) height;
}

bool Application::window_dimension_changed() const {
    return dimension_changed;
}


