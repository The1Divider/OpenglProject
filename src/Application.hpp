//
// Created by numpee on 2021-04-19.
//

#ifndef OPENGLPROJECT_APPLICATION_HPP
#define OPENGLPROJECT_APPLICATION_HPP


#include <GLFW/glfw3.h>
#include <ctime>
#include <string>

class Application {
    public:
        Application();

        static Application& get_instance();

        // returns window id
        GLFWwindow* get_window() const;

        // time properties
        float get_frame_time_delta() const;
        float get_time() const;

        // control
        void run();
        void exit();

        // dimensional properties
        int get_width() const;
        int get_height() const;
        float get_window_ratio() const;
        bool window_dimension_changed() const;

    private:

        // control state
        enum State { stateReady, stateRun, stateExit };
        State state;

        Application& operator=(const Application&) { return *this; }

        GLFWwindow* window{};

        // time
        float time{};
        float deltaTime{};

        // dimensions
        int width{};
        int height{};
        bool dimension_changed{};
        void detect_window_dimension_change();

    protected:
        Application(const Application&){};
        ~Application();

        std::string title;

        virtual void loop() = 0;
};


#endif //OPENGLPROJECT_APPLICATION_HPP
