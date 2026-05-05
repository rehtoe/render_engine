#include <stdio.h>
#include <iostream>
#include <cmath>

#include "source/sprite.h"
#include "source/canvas.h"
#include "source/pixelCanvas.h"


int main(int argc,  char** argv){
    std::string image_ph = "/home/rem/Pictures/misc/yo_monta_.jpg";
    
    Canvas myScreen(1280, 720, "Simulation Engine");

    
    PixelCanvas PC(1,1);
    int hh = 0, ss=50, vv=255;
    PC.setHSV(0,0,hh, ss, vv);
    PC.save(("bin/p_1.png"));

    std::string tst_img = "bin/p_1.png";
    Sprite sp(tst_img);
    Sprite s1, s2(tst_img), s3(tst_img), s4(tst_img);
    s1.load(tst_img);
    s1.setPosition(500,500);
    s2.setPosition(100, 100);
    s3.setPosition(200, 200);
    s4.setPosition(300, 300);
    sp.setPosition(250,250);
    float theta = 0;
    int xv = 2*cos(theta);
    int yv = 2*sin(theta);
    while (myScreen.isOpen()) {
        myScreen.clear();

        // 1. Logic: Update object positions
        xv = 2*cos(theta);
        yv = 2*sin(theta);
        sp.setPosition(100+xv, 100+yv);
        s1.setPosition(s1.x+xv, s1.y+yv);
        s2.setPosition(s2.x+xv, s2.y-yv);
        s3.setPosition(s3.x-xv, s3.y+yv);
        s4.setPosition(s4.x-xv, s4.y-yv);
        
        // 2. Render: Draw objects to the back buffer
        sp.draw();

        s1.draw();
        s2.draw();
        s3.draw();
        s4.draw();


        // 3. Display: Flip buffers
        myScreen.update();
        theta += 0.04f;
    }


/*
    if (!glfwInit()){ return -1; }
    // This creates the actual window object
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Rendered Window", NULL, NULL);
    
    if(!window){ glfwTerminate(); return -2; }
    
    glfwMakeContextCurrent(window);

    int screenWidth = 800, screenHeight = 450;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // This maps (0,0) to top-left and (width, height) to bottom-right
    glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    std::cin;
    float t = 1.5, kx = 3, ky = 1.5;
    int refX = 0, refY = 0;

    while (!glfwWindowShouldClose(window)) {
        // Clear the screen so we start with a blank slate every frame
        glClear(GL_COLOR_BUFFER_BIT);

        s1.setPosition(s1.x + refX, s1.y + refY);
        // Draw the sprite
        s1.draw();

        refX = kx*abs(log(2*t));
        refY = ky*sin(8*t);
        t = t + 0.01;
        // Swap buffers (Show the image we just drew)
        glfwSwapBuffers(window);

        // Check for exit clicks/keyboard input
        glfwPollEvents();
    }
        
*/
    return 0;
}