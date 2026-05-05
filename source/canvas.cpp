#include "canvas.h"

void Canvas::clear() {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
}

void Canvas::update() {
        glfwSwapBuffers(window);
        glfwPollEvents();
}

bool Canvas::isOpen() {
    return !glfwWindowShouldClose(window);
}