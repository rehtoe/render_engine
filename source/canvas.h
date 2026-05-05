#ifndef CANVAS_H
#define CANVAS_H

#include <opencv2/opencv.hpp>
#include <GLFW/glfw3.h>
#include <string>

class Canvas {
public:
    GLFWwindow* window;
    std::string name;
    int width, height;

    Canvas(int w, int h, const char* title) : width(w), height(h) {
        if (!glfwInit()) throw std::runtime_error("Failed to init GLFW");
        
        window = glfwCreateWindow(w, h, title, NULL, NULL);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create Window");
        }
        
        glfwMakeContextCurrent(window);
        // Map 1:1 pixel coordinates
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
    }

    // Call this at the start of your frame
    void clear();

    // Call this only after ALL objects have moved and drawn
    void update();

    bool isOpen();

    ~Canvas() { glfwTerminate(); }
};

#endif // CANVAS_H